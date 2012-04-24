<?php
  /**
   * TODO: review documentation and provide links to help pages.
   */

  // Polyfills
  $form['at-layout']['polyfills'] = array(
    '#type' => 'fieldset',
    '#title' => t('Polyfills'),
  );
  $form['at-layout']['polyfills']['fills'] = array(
    '#type' => 'fieldset',
    '#title' => t('Polyfills'),
    '#description' => t('<h3>Polyfills</h3>'),
  );

  // HTML5 shiv
  $form['at-layout']['polyfills']['fills']['load_html5js'] = array(
    '#type' => 'checkbox',
    '#title' => t('HTML5 support in IE'),
    '#description' => t('By checking this setting the site will load the <a href="!link" target="_blank">html5shiv</a>. Turning this off will be bad news for IE6-8.', array('!link' => '//github.com/aFarkas/html5shiv')),
    '#default_value' => at_get_setting('load_html5js'),
  );

  // Rounding error fix (CSS)
  $form['at-layout']['polyfills']['fills']['load_ltie8css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix CSS rounding errors in IE6-7'),
    '#description' => t('Load a stylesheet that fixes percentage rounding errors in IE6-7. You need this if you are using Gpanels or Panels layouts.'),
    '#default_value' => at_get_setting('load_ltie8css'),
  );

  // Respond.js
  $form['at-layout']['polyfills']['fills']['load_respondjs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Media query support for IE6-8'),
    '#description' => t('By checking this setting IE6, 7 and 8 will rely on <a href="!link" target="_blank">respond.js</a> to set the layout.', array('!link' => '//github.com/scottjehl/Respond', '!link2' => '//github.com/scottjehl/Respond/issues')),
    '#default_value' => at_get_setting('load_respondjs'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // Boxsizing.htc
  $form['at-layout']['polyfills']['fills']['load_boxsizinghtc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Box Sizing support for IE6-7'),
    '#description' => t('<a href="!link" target="_blank">Box Sizing HTC</a> enables CSS3 <code>box-sizing</code> for IE6-IE8.', array('!link' => '//github.com/Schepp/box-sizing-polyfill')),
    '#default_value' => at_get_setting('load_boxsizinghtc'),
  );

  // PIE
 $form['at-layout']['polyfills']['fills']['pie']['load_pie'] = array(
    '#type' => 'checkbox',
    '#title' => t('PIE'),
    '#description' => t('<a href="!link" target="_blank">PIE</a> enabes CSS3 backwards compatibility for IE. Turn PIE off if you are not using it, its 40kb.', array('!link' => 'http://css3pie.com')),
    '#default_value' => at_get_setting('load_pie'),
  );
  $form['at-layout']['polyfills']['fills']['pie']['pie_crust'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional options for PIE'),
    '#states' => array(
      'visible' => array('input[name="load_pie"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['polyfills']['fills']['pie']['pie_crust']['which_pie'] = array(
    '#type' => 'select',
    '#title' => t('Select which version of PIE to load'),
    '#default_value' => at_get_setting('which_pie'),
    '#options' => array(
      'PIE.htc' => 'PIE.htc - default',
      'PIE.php' => 'PIE.php - use if .htc does not work on your server',
      'PIE.js' => 'PIE.js - js implimentation, see the PIE docs',
    ),
  );
  $form['at-layout']['polyfills']['fills']['pie']['pie_crust']['disble_pie_for_ie9'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable PIE for IE9'),
    '#description' => t('IE9 supports some CSS3, optionally disable PIE support in IE9.'),
    '#default_value' => at_get_setting('disble_pie_for_ie9'),
  );

  // selectivizr is a JavaScript utility that emulates CSS3 pseudo-classes and attribute selectors in Internet Explorer 6-8
  $form['at-layout']['polyfills']['fills']['load_selectivizr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Selectivizr'),
    '#description' => t('<a href="!link" target="_blank">Selectivizr</a> is a JavaScript utility that emulates CSS3 pseudo-classes and attribute selectors in Internet Explorer 6-8.', array('!link' => 'http://selectivizr.com')),
    '#default_value' => at_get_setting('load_selectivizr'),
  );

  // Scalefix
  $form['at-layout']['polyfills']['fills']['load_scalefixjs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scalefix for iOS'),
    '#description' => t('Fixes the iOS Orientationchange zoom bug.'),
    '#default_value' => at_get_setting('load_scalefixjs'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
