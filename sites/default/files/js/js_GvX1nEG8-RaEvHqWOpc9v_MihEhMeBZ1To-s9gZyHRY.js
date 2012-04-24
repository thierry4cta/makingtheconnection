
// bootstrap
Drupal.behaviors.jstimer = {
  attach: function(context) {
    Drupal.jstimer.countdown_auto_attach(
      new Array(
        new Drupal.jstimer.jst_timer()
      )
    );
  }
}

// Namespace for most of the javascript functions.
Drupal.jstimer = {};

// Array that holds all elements that need to be updated.
Drupal.jstimer.timer_stack = new Array();

// Attach all active widgets to their respective dom objects.
Drupal.jstimer.countdown_auto_attach = function (jstimer_active_widgets) {

  // Call .attach() on the active widget items.
  for (var i=0; i<jstimer_active_widgets.length; i++) {
    jstimer_active_widgets[i].attach();
  }

  // If you have any widget items, start the timing loop.
  if ( Drupal.jstimer.timer_stack.length > 0 ) {
    Drupal.jstimer.timer_loop();
  }

}

// The timing loop.
Drupal.jstimer.timer_loop = function() {
  // run backwards so we can remove items and not messup the loop data.
  for (var i = Drupal.jstimer.timer_stack.length - 1; i >= 0; i--) {
    if ( Drupal.jstimer.timer_stack[i].update() == false ) {
      Drupal.jstimer.timer_stack.splice(i, 1);
    }
  }

  // Stop the timer if there are not more timer items.
  if ( Drupal.jstimer.timer_stack.length > 0 ) {
    setTimeout('Drupal.jstimer.timer_loop()',999);
  }
}


/*
 * Timer widget
 */
Drupal.jstimer.formats = ['<em>(%dow% %moy%%day%)</em><br/>%days% days + %hours%:%mins%:%secs%','Only %days% days, %hours% hours, %mins% minutes and %secs% seconds left','%days% shopping days left','<em>(%dow% %moy%%day%)</em><br/>%days% days + %hours%:%mins%:%secs%','<table id="CountdownTimer"><tr id="TimerNos"><td>%days%</td><td>%hours%</td><td>%mins%</td><td>%secs%</td></tr><tr id="TimerLtrs"><td>days</td><td>hours</td><td>minutes</td><td>secs</td></tr></table>','<table id="CountdownTimer"><tr id="TimerNos"><td>%days%</td><td>%hours%</td><td>%mins%</td><td>%secs%</td></tr><tr id="TimerLtrs"><td>jours</td><td>heures</td><td>minutes</td><td>secondes</td></tr></table><br/>'];

Drupal.jstimer.jst_timer = function() {
  this.selector = ".jst_timer";
  this.attach = function() {
    jQuery(this.selector).each(
      function(i) {  // i is the position in the each fieldset
        var t = new Drupal.jstimer.jst_timer_item(jQuery(this));
        if ( t.parse_microformat_success == 1 ) {
          Drupal.jstimer.timer_stack[Drupal.jstimer.timer_stack.length] = t;
        }
      }
    );
  }
}

Drupal.jstimer.jst_timer_item = function(ele) {

  // class methods first so you can use them in the constructor.
  this.loadProps = function() {
    for (var prop in this.props) {
      var prop_selector = "span[class="+prop+"]";
      if ( this.element.children(prop_selector).length > 0 ) {
        this.props[prop] = this.element.children(prop_selector).html();
      }
    }

    if ( String(this.props['format_txt']).match("'") ) {
      this.props['format_txt'] = "<span style=\"color:red;\">Format may not contain single quotes(').</span>";
    }

    // format_txt overrides format_num.
    if ( this.props['format_txt'] != "" ) {
      this.outformat = this.props['format_txt'];
    } else {
      if (Drupal.jstimer.formats[this.props['format_num']] != undefined) {
        this.outformat = Drupal.jstimer.formats[this.props['format_num']];
      }
      else {
        this.outformat = Drupal.jstimer.formats[0];
      }
    }

  }

  this.parse_microformat = function() {

    // ajax calls re-run autoattach, make sure the selector is gone.
    if ( this.element.hasClass("jst_timer") ) {
      this.element.removeClass("jst_timer")
    }

    // If there is an interval, always use it.
    if ( this.props['interval'] != "" ) {
      var interval_val = parseInt(this.props['interval']);
      var date = new Date();
      this.to_date = date;
      this.to_date.setTime(date.getTime() + (interval_val*1000));
    } else {
      if ( this.props['datetime'] == "" ) {
        this.parse_microformat_success = 0;
        throw new Object({name:"NoDate",message:"Javascript Timer: Span with class=datetime not found within the timer span."});
      }
      var date = new Date();
      try {
        date.jstimer_set_iso8601_date(this.props['datetime']);
      }
      catch(e) {
        throw(e);
      }
      this.to_date = date;
      if ( this.props['current_server_time'] != "" ) {
        // this is a feedback time from the server to correct for small server-client time differences.
        // not used for normal block and node timers.
        var date_server = new Date();
        date_server.jstimer_set_iso8601_date(this.props['current_server_time']);
        var date_client = new Date();
        var adj = date_client.getTime() - date_server.getTime();
        // adjust target date to clients domain
        this.to_date.setTime(this.to_date.getTime() + adj);
      }
    }

    this.parse_microformat_success = 1;
  }



  this.update = function() {
    var now_date = new Date();
    var duration = this.get_duration(now_date, this.to_date);

    // If counting down and timer is completed, set timer complete statement, check for redirect, and end.
    if ( this.props['dir'] == "down" && duration.sign > 0 ) {

      // Set the timer complete statement.
      if (this.props['timer_complete_message'] != '') {
        this.element.html(this.props['timer_complete_message'] + '');
        // Clear message as we don't need to reset it again.
        this.props['timer_complete_message'] = '';
      }

      // If there is a complete message, alert it.
      if (this.props['tc_msg'] != '') {
        alert(this.props['tc_msg']);
        // Clear alert msg as we don't need to alert it again.
        this.props['tc_msg'] = '';
      }

      // If there is a redirect url and delay has been met, redirect.
      if (this.props['tc_redir'] != '' && (duration.diff >= this.props['tc_redir_delay'])) {
      	if (this.props['tc_redir'].match('<reload>')) {
      		window.location.reload(true);
      	}
      	else {
        	window.location = this.props['tc_redir'];
        }
        return false;
      }
      // Timer is completed
      return true;
    }


    var outhtml = new String(this.outformat);

    // try to handle counts with units first, use a try block because Drupal.formatPlural breaks javascript sometimes
    try {
      outhtml = outhtml.replace(/%years% years/,  Drupal.formatPlural(duration.years, "1 year", "@count years"));
      outhtml = outhtml.replace(/%ydays% days/,   Drupal.formatPlural(duration.days, "1 day", "@count days"));
      outhtml = outhtml.replace(/%days% days/,    Drupal.formatPlural(duration.tot_days, "1 day", "@count days"));
      outhtml = outhtml.replace(/%hours% hours/,  Drupal.formatPlural(duration.hours, "1 hour", "@count hours"));
      outhtml = outhtml.replace(/%mins% minutes/, Drupal.formatPlural(duration.minutes, "1 minute", "@count minutes"));
      outhtml = outhtml.replace(/%secs% seconds/, Drupal.formatPlural(duration.seconds, "1 second", "@count seconds"));
      outhtml = outhtml.replace(/%months% months/, Drupal.formatPlural(duration.months, "1 month", "@count months"));
      outhtml = outhtml.replace(/%tot_months% months/, Drupal.formatPlural(duration.tot_months, "1 month", "@count months"));
    }
    catch(e){
      // suppress errors
    }

    //handle counts without units
    outhtml = outhtml.replace(/%years%/, duration.years);
    outhtml = outhtml.replace(/%ydays%/, duration.days);
    outhtml = outhtml.replace(/%days%/, duration.tot_days);
    outhtml = outhtml.replace(/%hours%/, LZ(duration.hours));
    outhtml = outhtml.replace(/%mins%/, LZ(duration.minutes));
    outhtml = outhtml.replace(/%secs%/, LZ(duration.seconds));
    outhtml = outhtml.replace(/%hours_nopad%/, duration.hours);
    outhtml = outhtml.replace(/%mins_nopad%/, duration.minutes);
    outhtml = outhtml.replace(/%secs_nopad%/, duration.seconds);
    outhtml = outhtml.replace(/%sign%/, duration.sign < 0 ? '-' : '+');
    outhtml = outhtml.replace(/%months%/, duration.months);
    outhtml = outhtml.replace(/%tot_months%/, duration.tot_months);

    // Proximity styling.
    if (this.props['highlight'][0] != undefined && this.props['highlight'][0] != '' && this.props['dir'] == "down" && (duration.diff <= (this.props['threshold'] * 60))) {
      this.element.html('<span ' + this.props['highlight'][0] + '=' + this.props['highlight'][1] + '>' +  outhtml + '</span>');
    } else {
      this.element.html(outhtml);
    }

    return true;
  }

  this.get_duration = function(now, target) {
    var dur = {diff:0, sign:0, years:0, months:0, days:0, hours:0, minutes:0, seconds:0, tot_months:0, tot_days:0};
    dur.diff = Math.floor((now.getTime() - target.getTime()) / 1000);
    if ( dur.diff < 0 ) {
      dur.sign = -1;
      dur.diff = Math.abs(dur.diff);
    } else {
      dur.sign = 1;
    }

    dur.years = Math.floor(dur.diff / 60 / 60 / 24 / 365.25);

    // Use calendar months, using months based on seconds is problematic.
    if(now.getFullYear() == target.getFullYear()) {
       dur.tot_months = Math.abs(target.getMonth() - now.getMonth());
       dur.months = dur.tot_months;
    } else {
      dur.tot_months = 11 - now.getMonth();
      dur.tot_months += target.getMonth() + 1;
      dur.tot_months += (target.getFullYear() - now.getFullYear() - 1) * 12;
      dur.months = dur.tot_months - (dur.years * 12);
    }

    dur.tot_days = Math.floor(dur.diff / 60 / 60 / 24);
    dur.days = Math.ceil(dur.tot_days - (dur.years * 365.25));
    dur.hours = Math.floor(dur.diff / 60 / 60) - (dur.tot_days * 24);
    dur.minutes = Math.floor(dur.diff / 60) - (dur.hours * 60) - (dur.tot_days * 24 * 60);
    dur.seconds = dur.diff - (dur.minutes * 60) - (dur.hours * 60 * 60) - (dur.tot_days * 24 * 60 * 60);
    return dur;
  }



  // begin constructor
  this.element = ele;

  // Defaults for each timer.
  this.props = {
    datetime: '',
    dir: 'down',
    format_num: 0,
    format_txt: '',
    timer_complete_message: new String('<em>Timer Completed</em>'),
    highlight: new String('style="color:red"').split(/=/),
    threshold: new Number('5'),
    tc_redir: new String(''),
    tc_redir_delay: new Number('3'),
    tc_msg: new String(''),
    interval: '',
    current_server_time: ''
  };
  this.loadProps();


  /* bootstrap, parse microformat, load object */
  try {
    this.parse_microformat();
  }
  catch(e) {
    alert(e.message);
    alert(jQuery(ele).html());
    this.parse_microformat_success = 0;
    return;
  }

  // replace the static stuff in the format string
  // this only needs to be done once, so here is a good spot.
  this.outformat = this.outformat.replace(/%day%/,   this.to_date.getDate());
  this.outformat = this.outformat.replace(/%month%/, this.to_date.getMonth() + 1);
  this.outformat = this.outformat.replace(/%year%/,  this.to_date.getFullYear());
  this.outformat = this.outformat.replace(/%moy%/,   this.to_date.jstimer_get_moy());
  this.outformat = this.outformat.replace(/%dow%/,   this.to_date.jstimer_get_dow());
}
// End of timer widget.





// Util functions
function LZ(x) {
  return (x >= 10 || x < 0 ? "" : "0") + x;
}

// iso8601 date parsing routines.  Extends the built-in javascript date object.
Date.prototype.jstimer_set_iso8601_date = function (string) {
  var iso8601_re = /^(?:(\d{4})(?:-(\d{2})(?:-(\d{2}))?)?)?(?:[T ](\d{2}):(\d{2})(?::(\d{2})(.\d+)?)?((?:[+-](\d{2}):(\d{2}))|Z)?)?$/;
  var date_bits = iso8601_re.exec(string);
  var date_obj = null;
  if ( date_bits ) {
    date_bits.shift();
    date_bits[1] && date_bits[1]--; // normalize month
    date_bits[6] && (date_bits[6] *= 1000); // convert mils
    date_obj = new Date(date_bits[0]||1970, date_bits[1]||0, date_bits[2]||0, date_bits[3]||0, date_bits[4]||0, date_bits[5]||0, date_bits[6]||0);

    //timezone handling
    var zone_offset = 0;  // in minutes
    var zone_plus_minus = date_bits[7] && date_bits[7].charAt(0);
    // get offset from isostring time to Z time
    if ( zone_plus_minus != 'Z' ) {
      zone_offset = ((date_bits[8] || 0) * 60) + (Number(date_bits[9]) || 0);
      if ( zone_plus_minus != '-' ) {
        zone_offset *= -1;
      }
    }
    // convert offset to localtime offset, will include daylight savings
    if ( zone_plus_minus ) {
      zone_offset -= date_obj.getTimezoneOffset();
    }
    if ( zone_offset ) {
      date_obj.setTime(date_obj.getTime() + zone_offset * 60000);
    }
  }

  // set this object to current localtime representation
  try {
    this.setTime(date_obj.getTime());
  }
  catch(e) {
    throw new Object({name:"DatePatternFail",message:"jstimer: Date does not have proper format (ISO8601, see readme.txt)."});
  }
}
Date.prototype.jstimer_get_moy = function () {
  var myMonths=new Array("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");
  return myMonths[this.getMonth()];
}
Date.prototype.jstimer_get_dow = function () {
  var myDays=["Sun","Mon","Tue","Wed","Thu","Fri","Sat","Sun"];
  return myDays[this.getDay()];
}
;
/**
* hoverIntent r6 // 2011.02.26 // jQuery 1.5.1+
* <http://cherne.net/brian/resources/jquery.hoverIntent.html>
* 
* @param  f  onMouseOver function || An object with configuration options
* @param  g  onMouseOut function  || Nothing (use configuration options object)
* @author    Brian Cherne brian(at)cherne(dot)net
*/
(function($){$.fn.hoverIntent=function(f,g){var cfg={sensitivity:7,interval:100,timeout:0};cfg=$.extend(cfg,g?{over:f,out:g}:f);var cX,cY,pX,pY;var track=function(ev){cX=ev.pageX;cY=ev.pageY};var compare=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);if((Math.abs(pX-cX)+Math.abs(pY-cY))<cfg.sensitivity){$(ob).unbind("mousemove",track);ob.hoverIntent_s=1;return cfg.over.apply(ob,[ev])}else{pX=cX;pY=cY;ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}};var delay=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);ob.hoverIntent_s=0;return cfg.out.apply(ob,[ev])};var handleHover=function(e){var ev=jQuery.extend({},e);var ob=this;if(ob.hoverIntent_t){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t)}if(e.type=="mouseenter"){pX=ev.pageX;pY=ev.pageY;$(ob).bind("mousemove",track);if(ob.hoverIntent_s!=1){ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}}else{$(ob).unbind("mousemove",track);if(ob.hoverIntent_s==1){ob.hoverIntent_t=setTimeout(function(){delay(ev,ob)},cfg.timeout)}}};return this.bind('mouseenter',handleHover).bind('mouseleave',handleHover)}})(jQuery);;
/* Copyright (c) 2010 Brandon Aaron (http://brandonaaron.net)
 * Licensed under the MIT License (LICENSE.txt).
 *
 * Version 2.1.2
 */
(function(a){a.fn.bgiframe=(a.browser.msie&&/msie 6\.0/i.test(navigator.userAgent)?function(d){d=a.extend({top:"auto",left:"auto",width:"auto",height:"auto",opacity:true,src:"javascript:false;"},d);var c='<iframe class="bgiframe"frameborder="0"tabindex="-1"src="'+d.src+'"style="display:block;position:absolute;z-index:-1;'+(d.opacity!==false?"filter:Alpha(Opacity='0');":"")+"top:"+(d.top=="auto"?"expression(((parseInt(this.parentNode.currentStyle.borderTopWidth)||0)*-1)+'px')":b(d.top))+";left:"+(d.left=="auto"?"expression(((parseInt(this.parentNode.currentStyle.borderLeftWidth)||0)*-1)+'px')":b(d.left))+";width:"+(d.width=="auto"?"expression(this.parentNode.offsetWidth+'px')":b(d.width))+";height:"+(d.height=="auto"?"expression(this.parentNode.offsetHeight+'px')":b(d.height))+';"/>';return this.each(function(){if(a(this).children("iframe.bgiframe").length===0){this.insertBefore(document.createElement(c),this.firstChild)}})}:function(){return this});a.fn.bgIframe=a.fn.bgiframe;function b(c){return c&&c.constructor===Number?c+"px":c}})(jQuery);;
/*
 * Superfish v1.4.8 - jQuery menu widget
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * CHANGELOG: http://users.tpg.com.au/j_birch/plugins/superfish/changelog.txt
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.superfish = function(op){
    var sf = $.fn.superfish,
      c = sf.c,
      $arrow = $(['<span class="',c.arrowClass,'"> &#187;</span>'].join('')),
      over = function(){
        var $$ = $(this), menu = getMenu($$);
        clearTimeout(menu.sfTimer);
        $$.showSuperfishUl().siblings().hideSuperfishUl();
      },
      out = function(){
        var $$ = $(this), menu = getMenu($$), o = sf.op;
        clearTimeout(menu.sfTimer);
        menu.sfTimer=setTimeout(function(){
          o.retainPath=($.inArray($$[0],o.$path)>-1);
          $$.hideSuperfishUl();
          if (o.$path.length && $$.parents(['li.',o.hoverClass].join('')).length<1){over.call(o.$path);}
        },o.delay);
      },
      getMenu = function($menu){
        var menu = $menu.parents(['ul.',c.menuClass,':first'].join(''))[0];
        sf.op = sf.o[menu.serial];
        return menu;
      },
      addArrow = function($a){ $a.addClass(c.anchorClass).append($arrow.clone()); };

    return this.each(function() {
      var s = this.serial = sf.o.length;
      var o = $.extend({},sf.defaults,op);
      o.$path = $('li.'+o.pathClass,this).slice(0,o.pathLevels).each(function(){
        $(this).addClass([o.hoverClass,c.bcClass].join(' '))
          .filter('li:has(ul)').removeClass(o.pathClass);
      });
      sf.o[s] = sf.op = o;

      $('li:has(ul)',this)[($.fn.hoverIntent && !o.disableHI) ? 'hoverIntent' : 'hover'](over,out).each(function() {
        if (o.autoArrows) addArrow( $('>a:first-child',this) );
      })
      .not('.'+c.bcClass)
        .hideSuperfishUl();

      var $a = $('a',this);
      $a.each(function(i){
        var $li = $a.eq(i).parents('li');
        $a.eq(i).focus(function(){over.call($li);}).blur(function(){out.call($li);});
      });
      o.onInit.call(this);

    }).each(function() {
      var menuClasses = [c.menuClass];
      if (sf.op.dropShadows  && !($.browser.msie && $.browser.version < 7)) menuClasses.push(c.shadowClass);
      $(this).addClass(menuClasses.join(' '));
    });
  };

  var sf = $.fn.superfish;
  sf.o = [];
  sf.op = {};
  sf.IE7fix = function(){
    var o = sf.op;
    if ($.browser.msie && $.browser.version > 6 && o.dropShadows && o.animation.opacity!=undefined)
      this.toggleClass(sf.c.shadowClass+'-off');
    };
  sf.c = {
    bcClass: 'sf-breadcrumb',
    menuClass: 'sf-js-enabled',
    anchorClass: 'sf-with-ul',
    arrowClass: 'sf-sub-indicator',
    shadowClass: 'sf-shadow'
  };
  sf.defaults = {
    hoverClass: 'sfHover',
    pathClass: 'overideThisToUse',
    pathLevels: 1,
    delay: 800,
    animation: {opacity:'show'},
    speed: 'normal',
    autoArrows: true,
    dropShadows: true,
    disableHI: false, // true disables hoverIntent detection
    onInit: function(){}, // callback functions
    onBeforeShow: function(){},
    onShow: function(){},
    onHide: function(){}
  };
  $.fn.extend({
    hideSuperfishUl : function(){
      var o = sf.op,
        not = (o.retainPath===true) ? o.$path : '';
      o.retainPath = false;
      var $ul = $(['li.',o.hoverClass].join(''),this).add(this).not(not).removeClass(o.hoverClass)
          .find('>ul').css({top: '-99999em'}).addClass('sf-hidden');
      o.onHide.call($ul);
      return this;
    },
    showSuperfishUl : function(){
      var o = sf.op,
        sh = sf.c.shadowClass+'-off',
        $ul = this.addClass(o.hoverClass)
          .find('>ul.sf-hidden').css({display: 'none', top: ''}).removeClass('sf-hidden');
      sf.IE7fix.call($ul);
      o.onBeforeShow.call($ul);
      $ul.animate(o.animation,o.speed,function(){ sf.IE7fix.call($ul); o.onShow.call($ul); });
      return this;
    }
  });
})(jQuery);;
/*
 * Supersubs v0.2b - jQuery plugin
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * This plugin automatically adjusts submenu widths of suckerfish-style menus to that of
 * their longest list item children. If you use this, please expect bugs and report them
 * to the jQuery Google Group with the word 'Superfish' in the subject line.
 *
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){ // $ will refer to jQuery within this closure
  $.fn.supersubs = function(options){
    var opts = $.extend({}, $.fn.supersubs.defaults, options);
    // return original object to support chaining
    return this.each(function() {
      // cache selections
      var $$ = $(this);
      // support metadata
      var o = $.meta ? $.extend({}, opts, $$.data()) : opts;
      // get the font size of menu.
      // .css('fontSize') returns various results cross-browser, so measure an em dash instead
      var fontsize = $('<li id="menu-fontsize">&#8212;</li>').css({
        'padding' : 0,
        'position' : 'absolute',
        'top' : '-99999em',
        'width' : 'auto'
      }).appendTo($$).width(); //clientWidth is faster, but was incorrect here
      // remove em dash
      $('#menu-fontsize').remove();

      // Jump on level if it's a "NavBar"
      if ($$.hasClass('sf-navbar')) {
        $$ = $('li > ul', $$);
      }
      // cache all ul elements 
      $ULs = $$.find('ul:not(.sf-megamenu)');
      // loop through each ul in menu
      $ULs.each(function(i) {
        // cache this ul
        var $ul = $ULs.eq(i);
        // get all (li) children of this ul
        var $LIs = $ul.children();
        // get all anchor grand-children
        var $As = $LIs.children('a');
        // force content to one line and save current float property
        var liFloat = $LIs.css('white-space','nowrap').css('float');
        // remove width restrictions and floats so elements remain vertically stacked
        var emWidth = $ul.add($LIs).add($As).css({
          'float' : 'none',
          'width'  : 'auto'
        })
        // this ul will now be shrink-wrapped to longest li due to position:absolute
        // so save its width as ems. Clientwidth is 2 times faster than .width() - thanks Dan Switzer
        .end().end()[0].clientWidth / fontsize;
        // add more width to ensure lines don't turn over at certain sizes in various browsers
        emWidth += o.extraWidth;
        // restrict to at least minWidth and at most maxWidth
        if (emWidth > o.maxWidth)    { emWidth = o.maxWidth; }
        else if (emWidth < o.minWidth)  { emWidth = o.minWidth; }
        emWidth += 'em';
        // set ul to width in ems
        $ul.css('width',emWidth);
        // restore li floats to avoid IE bugs
        // set li width to full width of this ul
        // revert white-space to normal
        $LIs.css({
          'float' : liFloat,
          'width' : '100%',
          'white-space' : 'normal'
        })
        // update offset position of descendant ul to reflect new width of parent
        .each(function(){
          var $childUl = $('>ul',this);
          var offsetDirection = $childUl.css('left')!==undefined ? 'left' : 'right';
          $childUl.css(offsetDirection,emWidth);
        });
      });
    });
  };
  // expose defaults
  $.fn.supersubs.defaults = {
    minWidth: 9, // requires em unit.
    maxWidth: 25, // requires em unit.
    extraWidth: 0 // extra width can ensure lines don't sometimes turn over due to slight browser differences in how they round-off values
  };
})(jQuery); // plugin code ends;
/*
 * Supposition v0.2 - an optional enhancer for Superfish jQuery menu widget.
 *
 * Copyright (c) 2008 Joel Birch - based mostly on work by Jesse Klaasse and credit goes largely to him.
 * Special thanks to Karl Swedberg for valuable input.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.supposition = function(){
    var $w = $(window), /*do this once instead of every onBeforeShow call*/
    _offset = function(dir) {
      return window[dir == 'y' ? 'pageYOffset' : 'pageXOffset']
      || document.documentElement && document.documentElement[dir=='y' ? 'scrollTop' : 'scrollLeft']
      || document.body[dir=='y' ? 'scrollTop' : 'scrollLeft'];
    },
    onHide = function(){
      this.css({bottom:''});
    },
    onBeforeShow = function(){
      this.each(function(){
        var $u = $(this);
        $u.css('display','block');
        var menuWidth = $u.width(),
        menuParentWidth = $u.closest('li').outerWidth(true),
        menuParentLeft = $u.closest('li').offset().left,
        totalRight = $w.width() + _offset('x'),
        menuRight = $u.offset().left + menuWidth,
        exactMenuWidth = (menuRight > (menuParentWidth + menuParentLeft)) ? menuWidth - (menuRight - (menuParentWidth + menuParentLeft)) : menuWidth;  
        if ($u.parents('.sf-js-enabled').hasClass('rtl')) {
          if (menuParentLeft < exactMenuWidth) {
            $u.css('left', menuParentWidth + 'px');
            $u.css('right', 'auto');
          }
        }
        else {
          if (menuRight > totalRight && menuParentLeft > menuWidth) {
            $u.css('right', menuParentWidth + 'px');
            $u.css('left', 'auto');
          }
        }
        var windowHeight = $w.height(),
        offsetTop = $u.offset().top,
        menuParentShadow = ($u.closest('.sf-menu').hasClass('sf-shadow') && $u.css('padding-bottom').length > 0) ? parseInt($u.css('padding-bottom').slice(0,-2)) : 0,
        menuParentHeight = ($u.closest('.sf-menu').hasClass('sf-vertical')) ? '-' + menuParentShadow : $u.parent().outerHeight(true) - menuParentShadow,
        menuHeight = $u.height(),
        baseline = windowHeight + _offset('y');
        var expandUp = ((offsetTop + menuHeight > baseline) && (offsetTop > menuHeight));
        if (expandUp) {
          $u.css('bottom', menuParentHeight + 'px');
          $u.css('top', 'auto');
        }
        $u.css('display','none');
      });
    };

    return this.each(function() {
      var o = $.fn.superfish.o[this.serial]; /* get this menu's options */

      /* if callbacks already set, store them */
      var _onBeforeShow = o.onBeforeShow,
      _onHide = o.onHide;

      $.extend($.fn.superfish.o[this.serial],{
        onBeforeShow: function() {
          onBeforeShow.call(this); /* fire our Supposition callback */
          _onBeforeShow.call(this); /* fire stored callbacks */
        },
        onHide: function() {
          onHide.call(this); /* fire our Supposition callback */
          _onHide.call(this); /* fire stored callbacks */
        }
      });
    });
  };
})(jQuery);;
/*
 * sf-Touchscreen v1.0b - Provides touchscreen compatibility for the jQuery Superfish plugin.
 *
 * Developer's note:
 * Built as a part of the Superfish project for Drupal (http://drupal.org/project/superfish) 
 * Found any bug? have any cool ideas? contact me right away! http://drupal.org/user/619294/contact
 *
 * jQuery version: 1.3.x or higher.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */

(function($){
  $.fn.sftouchscreen = function() {
    // Return original object to support chaining.
    return this.each( function() {
      // Select hyperlinks from parent menu items.
      $(this).find('li > ul').closest('li').children('a').each( function() {
        var $item = $(this);
        // No .toggle() here as it's not possible to reset it.
        $item.click( function(event){
          // Already clicked? proceed to the URI.
          if ($item.hasClass('sf-clicked')) {
            var $uri = $item.attr('href');
            window.location = $uri;
          }
          else {
            event.preventDefault();
            $item.addClass('sf-clicked');
          }
        }).closest('li').mouseleave( function(){
          // So, we reset everything.
          $item.removeClass('sf-clicked');
        });
      });
    });
  };
})(jQuery);;
// $Id: compact_forms.js,v 1.11 2011/01/09 05:51:15 sun Exp $

(function ($) {

Drupal.compactForms = {};

/**
 * Compact Forms jQuery plugin.
 */
$.fn.compactForm = function (stars) {
  stars = stars || 0;

  this.each(function () {
    $(this).addClass('compact-form').find('label').each(function () {
      var context = this.form;
      var $label = $(this);
      if (!$label.attr('for')) {
        return;
      }
      var $field = $('#' + $label.attr('for'), context);
      if (!$field.length || !$field.is('input:text,input:password,textarea,input[type=email]')) {
        return;
      }
      // Store the initial field value, in case the browser is going to
      // automatically fill it in upon focus.
      var initial_value = $field.val();

      if (initial_value != '') {
        // Firefox doesn't like .hide() here for some reason.
        $label.css('display', 'none');
      }

      $label.parent().addClass('compact-form-wrapper');
      $label.addClass('compact-form-label');
      $field.addClass('compact-form-field');

      if (stars === 0) {
        $label.find('.form-required').hide();
      }
      else if (stars === 2) {
        $label.find('.form-required').insertAfter($field).prepend('&nbsp;');
      }

      $field.focus(function () {
        // Some browsers (e.g., Firefox) are automatically inserting a stored
        // username and password into login forms. In case the password field is
        // manually emptied afterwards, and the user jumps back to the username
        // field (without changing it), and forth to the password field, then
        // the browser automatically re-inserts the password again. Therefore,
        // we also need to test against the initial field value.
        if ($field.val() === initial_value || $field.val() === '') {
          $label.fadeOut('fast');
        }
      });

      $field.blur(function () {
        if ($field.val() === '') {
          $label.fadeIn('slow');
        }
      });

      // Chrome adds passwords after page load, so we need to track changes.
      $field.change(function () {
        if ($field.get(0) != document.activeElement) {
          if ($field.val() === '') {
            $label.fadeIn('fast');
          }
          else {
            $label.css('display', 'none');
          }
        }
      });
    });
  });
};

/**
 * Attach compact forms behavior to all enabled forms upon page load.
 */
Drupal.behaviors.compactForms = {
  attach: function (context, settings) {
    if (!settings || !settings.compactForms) {
      return;
    }
    $('#' + settings.compactForms.forms.join(',#'), context).compactForm(settings.compactForms.stars);

    // Safari adds passwords without triggering any event after page load.
    // We therefore need to wait a bit and then check for field values.
    if ($.browser.safari) {
      setTimeout(Drupal.compactForms.fixSafari, 200);
    }
  }
};

/**
 * Checks for field values and hides the corresponding label if non-empty.
 *
 * @todo Convert $.fn.compactForm to always use a function like this.
 */
Drupal.compactForms.fixSafari = function () {
  $('label.compact-form-label').each(function () {
    var $label = $(this);
    var context = this.form;
    if ($('#' + $label.attr('for'), context).val() != '') {
      $label.css('display', 'none');
    }
  });
}

})(jQuery);
;
(function ($) {

/**
 * A progressbar object. Initialized with the given id. Must be inserted into
 * the DOM afterwards through progressBar.element.
 *
 * method is the function which will perform the HTTP request to get the
 * progress bar state. Either "GET" or "POST".
 *
 * e.g. pb = new progressBar('myProgressBar');
 *      some_element.appendChild(pb.element);
 */
Drupal.progressBar = function (id, updateCallback, method, errorCallback) {
  var pb = this;
  this.id = id;
  this.method = method || 'GET';
  this.updateCallback = updateCallback;
  this.errorCallback = errorCallback;

  // The WAI-ARIA setting aria-live="polite" will announce changes after users
  // have completed their current activity and not interrupt the screen reader.
  this.element = $('<div class="progress" aria-live="polite"></div>').attr('id', id);
  this.element.html('<div class="bar"><div class="filled"></div></div>' +
                    '<div class="percentage"></div>' +
                    '<div class="message">&nbsp;</div>');
};

/**
 * Set the percentage and status message for the progressbar.
 */
Drupal.progressBar.prototype.setProgress = function (percentage, message) {
  if (percentage >= 0 && percentage <= 100) {
    $('div.filled', this.element).css('width', percentage + '%');
    $('div.percentage', this.element).html(percentage + '%');
  }
  $('div.message', this.element).html(message);
  if (this.updateCallback) {
    this.updateCallback(percentage, message, this);
  }
};

/**
 * Start monitoring progress via Ajax.
 */
Drupal.progressBar.prototype.startMonitoring = function (uri, delay) {
  this.delay = delay;
  this.uri = uri;
  this.sendPing();
};

/**
 * Stop monitoring progress via Ajax.
 */
Drupal.progressBar.prototype.stopMonitoring = function () {
  clearTimeout(this.timer);
  // This allows monitoring to be stopped from within the callback.
  this.uri = null;
};

/**
 * Request progress data from server.
 */
Drupal.progressBar.prototype.sendPing = function () {
  if (this.timer) {
    clearTimeout(this.timer);
  }
  if (this.uri) {
    var pb = this;
    // When doing a post request, you need non-null data. Otherwise a
    // HTTP 411 or HTTP 406 (with Apache mod_security) error may result.
    $.ajax({
      type: this.method,
      url: this.uri,
      data: '',
      dataType: 'json',
      success: function (progress) {
        // Display errors.
        if (progress.status == 0) {
          pb.displayError(progress.data);
          return;
        }
        // Update display.
        pb.setProgress(progress.percentage, progress.message);
        // Schedule next timer.
        pb.timer = setTimeout(function () { pb.sendPing(); }, pb.delay);
      },
      error: function (xmlhttp) {
        pb.displayError(Drupal.ajaxError(xmlhttp, pb.uri));
      }
    });
  }
};

/**
 * Display errors on the page.
 */
Drupal.progressBar.prototype.displayError = function (string) {
  var error = $('<div class="messages error"></div>').html(string);
  $(this.element).before(error).hide();

  if (this.errorCallback) {
    this.errorCallback(this);
  }
};

})(jQuery);
;

/**
 * JavaScript behaviors for the front-end display of webforms.
 */

(function ($) {

Drupal.behaviors.webform = Drupal.behaviors.webform || {};

Drupal.behaviors.webform.attach = function(context) {
  // Calendar datepicker behavior.
  Drupal.webform.datepicker(context);
};

Drupal.webform = Drupal.webform || {};

Drupal.webform.datepicker = function(context) {
  $('div.webform-datepicker').each(function() {
    var $webformDatepicker = $(this);
    var $calendar = $webformDatepicker.find('input.webform-calendar');
    var startDate = $calendar[0].className.replace(/.*webform-calendar-start-(\d{4}-\d{2}-\d{2}).*/, '$1').split('-');
    var endDate = $calendar[0].className.replace(/.*webform-calendar-end-(\d{4}-\d{2}-\d{2}).*/, '$1').split('-');
    var firstDay = $calendar[0].className.replace(/.*webform-calendar-day-(\d).*/, '$1');
    // Convert date strings into actual Date objects.
    startDate = new Date(startDate[0], startDate[1] - 1, startDate[2]);
    endDate = new Date(endDate[0], endDate[1] - 1, endDate[2]);

    // Ensure that start comes before end for datepicker.
    if (startDate > endDate) {
      var laterDate = startDate;
      startDate = endDate;
      endDate = laterDate;
    }

    var startYear = startDate.getFullYear();
    var endYear = endDate.getFullYear();

    // Set up the jQuery datepicker element.
    $calendar.datepicker({
      dateFormat: 'yy-mm-dd',
      yearRange: startYear + ':' + endYear,
      firstDay: parseInt(firstDay),
      minDate: startDate,
      maxDate: endDate,
      onSelect: function(dateText, inst) {
        var date = dateText.split('-');
        $webformDatepicker.find('select.year, input.year').val(+date[0]);
        $webformDatepicker.find('select.month').val(+date[1]);
        $webformDatepicker.find('select.day').val(+date[2]);
      },
      beforeShow: function(input, inst) {
        // Get the select list values.
        var year = $webformDatepicker.find('select.year, input.year').val();
        var month = $webformDatepicker.find('select.month').val();
        var day = $webformDatepicker.find('select.day').val();

        // If empty, default to the current year/month/day in the popup.
        var today = new Date();
        year = year ? year : today.getFullYear();
        month = month ? month : today.getMonth() + 1;
        day = day ? day : today.getDate();

        // Make sure that the default year fits in the available options.
        year = (year < startYear || year > endYear) ? startYear : year;

        // jQuery UI Datepicker will read the input field and base its date off
        // of that, even though in our case the input field is a button.
        $(input).val(year + '-' + month + '-' + day);
      }
    });

    // Prevent the calendar button from submitting the form.
    $calendar.click(function(event) {
      $(this).focus();
      event.preventDefault();
    });
  });
}

})(jQuery);
;
(function ($) {

$(document).ready(function() {

  // Accepts a string; returns the string with regex metacharacters escaped. The returned string
  // can safely be used at any point within a regex to match the provided literal string. Escaped
  // characters are [ ] { } ( ) * + ? - . , \ ^ $ # and whitespace. The character | is excluded
  // in this function as it's used to separate the domains names.
  RegExp.escapeDomains = function(text) {
    return (text) ? text.replace(/[-[\]{}()*+?.,\\^$#\s]/g, "\\$&") : '';
  }

  // Attach onclick event to document only and catch clicks on all elements.
  $(document.body).click(function(event) {
    // Catch the closest surrounding link of a clicked element.
    $(event.target).closest("a,area").each(function() {

      var ga = Drupal.settings.googleanalytics;
      // Expression to check for absolute internal links.
      var isInternal = new RegExp("^(https?):\/\/" + window.location.host, "i");
      // Expression to check for special links like gotwo.module /go/* links.
      var isInternalSpecial = new RegExp("(\/go\/.*)$", "i");
      // Expression to check for download links.
      var isDownload = new RegExp("\\.(" + ga.trackDownloadExtensions + ")$", "i");
      // Expression to check for the sites cross domains.
      var isCrossDomain = new RegExp("^(https?|ftp|news|nntp|telnet|irc|ssh|sftp|webcal):\/\/.*(" + RegExp.escapeDomains(ga.trackCrossDomains) + ")", "i");

      // Is the clicked URL internal?
      if (isInternal.test(this.href)) {
        // Is download tracking activated and the file extension configured for download tracking?
        if (ga.trackDownload && isDownload.test(this.href)) {
          // Download link clicked.
          var extension = isDownload.exec(this.href);
          _gaq.push(["_trackEvent", "Downloads", extension[1].toUpperCase(), this.href.replace(isInternal, '')]);
        }
        else if (isInternalSpecial.test(this.href)) {
          // Keep the internal URL for Google Analytics website overlay intact.
          _gaq.push(["_trackPageview", this.href.replace(isInternal, '')]);
        }
      }
      else {
        if (ga.trackMailto && $(this).is("a[href^=mailto:],area[href^=mailto:]")) {
          // Mailto link clicked.
          _gaq.push(["_trackEvent", "Mails", "Click", this.href.substring(7)]);
        }
        else if (ga.trackOutbound && this.href) {
          if (ga.trackDomainMode == 2 && isCrossDomain.test(this.href)) {
            // Top-level cross domain clicked. document.location is handled by _link internally.
            _gaq.push(["_link", this.href]);
          }
          else if (ga.trackOutboundAsPageview) {
            // Track all external links as page views after URL cleanup.
            // Currently required, if click should be tracked as goal.
            _gaq.push(["_trackPageview", '/outbound/' + this.href.replace(/^(https?|ftp|news|nntp|telnet|irc|ssh|sftp|webcal):\/\//i, '').split('/').join('--')]);
          }
          else {
            // External link clicked.
            _gaq.push(["_trackEvent", "Outbound links", "Click", this.href]);
          }
        }
      }
    });
  });
});

})(jQuery);
;
