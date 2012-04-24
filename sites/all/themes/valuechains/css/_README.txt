
# First read this about SASS, its very important!

  There is more information regarding working with SASS in the SASS
  CSS folder _README, however, you need to be aware that if you set
  Compass to watch the SASS folder or any SCSS file in this theme
  it will OVERWRITE the CSS file/s in your sub-themes CSS directory!

  To prevent this ever happening you can delete the config.rb file in
  the sub-theme root (unless you are actually planning on using SASS,
  in which case you will want to keep it).


# Working with Responsive Design in Adaptivetheme

  The subtheme is designed to be "mobile first". In short this means to
  first load a set of global styles, the progressively add styles for larger 
  devices using media queries.

  Its important to note that you do not have to follow a mobile first approach.
  Many designers and themers simply load the majority of their themes design
  in the global styles and then override them in media queries.

  You can do both in Adaptivetheme - it's merely a matter of where you place
  the majority of your styles, and what theme settings you choose in the 
  Appearance settings for your sub-theme.
  
  Lets examine the CSS file structure of Adaptivetheme and look at how each 
  file is loaded. From this you will be able to deduce what approach might work 
  for you, and where you should be placing your CSS.

  ## Global Styles

  The global styles do not target any specific device - they always load for all
  devices, however you can unset each one or even all theme quite easily.
  
  global.css holds an array of @imports that pull in all the others. You can use
  this to remove or comment out unwanted styles.

  All the global stylesheets are prefixed with the name "global", for example
  global.base.css, global.blocks.css and so on. The selectors are extensive
  and you should delete unused selectors before going live to reduce CSS weight.
  You can use cleancss.com or a better way is just use SASS does this for you.

  Each file includes a lot of comments and documentation, please review each of
  the global CSS files for more help.

  If you are doing mobile first then you will probably keep things to a minimum
  in these files. If you are doing mobile last approach, then you will place the
  majority of your CSS in these files.

  ## Responsive Styles

  Adaptivetheme 7.x-3.x has two "modes", a development mode and a production mode.
  Depending on what mode you are in the stylesheets will load differently.

  To change the mode see the "Settings" tab in the Appearance settings for your theme.

  In development mode the responsive stylesheets will load in individual link elements
  with the media query in media attribute. This allows them to load directly into the
  browser and you will see your CSS changes immediately, as per normal CSS development.
 
  There are six of these responsive stylesheets - one for each break point set in the 
  theme settings:
  
  responsive.smartphone.landscape.css
  responsive.smartphone.portrait.css
  responsive.tablet.landscape.css
  responsive.tablet.portrait.css
  responsive.standard.bigscreen.css

  Its important to know that these files DO NOT contain the media queries (in case you
  were looking for them), instead they load in the <link> elements media attribute - 
  remember, these files only load when in Development Mode.

  When in production mode all the responsive stylesheets are aggregated into one file
  and it uses embedded @media queries. 
  
  This file loads from your public files directory. AT does this, not Drupal core - 
  it has nothing to do with Performance Settings or Core CSS aggregation (which you 
  should also turn on when going live!).

  For a mobile first approach you will place minimal styles in the global stylesheets
  and instead place the majority of your CSS in the responsive stylesheets - progressively
  enhancing the design for each device range. This is especially useful for avoiding
  things such as large background images for small screens and for reducing the CSS
  overhead for mobile connections.

  ## Overlapping Media queries

  By default the media queries in Adaptivetheme are "stacked", meaning they do not
  overlap. This makes it very easy to target one set of devices and not have those
  styles leak over into others. However it can also mean you need to duplicate a lot
  of CSS that you would rather cascades. To achieve this  you can either modify the
  media queries to only use a min-width, or you can use a special file called:

  responsive.cascade.css

  This file has embedded media queries which means you MUST set them yourself. Defaults
  are provided.

  Allowing styles to cascade can result in a huge saving on total CSS weight and speed
  up development. It can also be harder to maintain and you really need to understand
  cascade and inheritance, not to mention selector specificity, to a high degree.


# Internet Explorer

  AT can load IE conditional stylsheets from you sub-themes info file. Please see
  adaptivetheme_subtheme.info. Its strait forward and the same as adding other
  stylesheets.

  Adaptivetheme also includes special conditional classes on the HTML element
  which allow you to easily target styles at specific version of IE.

  These are the classes you can use:

 .iem7 (IE7 Mobile)
 .lt-ie7 (less than IE7)
 .lt-ie8 (less than IE8)
 .lt-ie9 (less than IE9)

  Use these if you only have a small number of overrides. They are useful especially
  if you do not want to load a conditional stylesheet just for a few minor adjustments
  or if you only want to load one conditional stylesheet yet target different versions
  of IE in one file.


# Support

  Ping me on Skype if you really need help: jmburnz, otherwise support my work
  by joining my theme club, it really does fund my contrib projects:

  http://adaptivethemes.com/pricing

  Or, you could get radical and file a support issue, even post a patch (which makes
  me very happy):

  http://drupal.org/project/issues/adaptivetheme

