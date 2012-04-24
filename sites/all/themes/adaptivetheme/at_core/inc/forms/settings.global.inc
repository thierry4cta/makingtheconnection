<?php
  /**
   * TODO: review documentation and provide links to help pages.
   */

  // Global Settings
  $form['at-layout']['global-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );

  // Mode
  $form['at-layout']['global-settings']['mode'] = array(
    '#type' => 'fieldset',
    '#title' => t('Production Mode'),
    '#description' => t('<h3>Production Mode</h3>'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['global-settings']['mode']['production_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Production Mode'),
    '#description' => t('Enabling Production mode reduces HTTP requests by aggregating the responsive stylesheets into one CSS file and uses embedded media queries. Enable this after you have finished writing your CSS styles. If you later change any styles in the responsive stylesheets you will need re-save the theme settings to re-write the aggregated CSS file.'),
    '#default_value' => at_get_setting('production_mode'),
  );

  // Set default layout
  $form['at-layout']['global-settings']['default-layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile first or Mobile last'),
    '#description' => t('<h3>Mobile first or Desktop first</h3>'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['global-settings']['default-layout']['global_default_layout'] = array(
    '#type' => 'radios',
    '#description' => t('Adaptivetheme supports both mobile first and desktop first design approaches.'),
    '#default_value' => at_get_setting('global_default_layout'),
    '#options' => array(
      'smartphone-portrait'  => t('Mobile first'),
      'standard-layout'      => t('Desktop first'),
    ),
  );

  // Cascading media queries
  $form['at-layout']['global-settings']['cascading-mediaqueries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cascading Media Queries'),
    '#description' => t('<h3>Cascading Media Queries</h3>'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['global-settings']['cascading-mediaqueries']['enable_cascading_media_queries'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Enable the responsive.cascade.css file'),
    '#description' => t('Use <a href="http://zomigi.com/blog/essential-considerations-for-crafting-quality-media-queries/#mq-overlap-stack" target="_blank">overlapped media queries</a>. These are are in a seperate file: <code>themeName/css/responsive.cascade.css</code>, you must set the media queries in this file manually!'),
    '#default_value' => at_get_setting('enable_cascading_media_queries'),

  );
  $form['at-layout']['global-settings']['cascading-mediaqueries']['cascade_media_query'] = array(
    '#type' => 'textfield',
    '#description' => t('Enter the smallest min-width in your <code>responsive.cascade.css</code> file, this is used when loading the file in Development mode.'),
    '#default_value' => at_get_setting('cascade_media_query'),
    '#field_prefix' => '@media',
    '#states' => array(
      'invisible' => array('input[name="production_mode"]' => array('checked' => TRUE)),
      'disabled' => array('input[name="enable_cascading_media_queries"]' => array('checked' => FALSE)),
    ),
  );

  // Disable responsive layout
  $form['at-layout']['global-settings']['disable-rs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disable Responsive Layout'),
    '#description' => t('<h3>Disable Responsive Layout</h3>'),
  );
  $form['at-layout']['global-settings']['disable-rs']['disable_responsive_styles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable responsive layout and styles'),
    '#description' => t('By checking this setting the site will use only the Standard layout and the global styles. You can turn this back on at any time.'),
    '#default_value' => at_get_setting('disable_responsive_styles'),
  );

  // Enable extensions (really we just unhide the extensions)
  $form['at-layout']['global-settings']['extensions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable Extensions'),
    '#description' => t('<h3>Enable Extensions</h3>'),
  );
  $form['at-layout']['global-settings']['extensions']['enable_extensions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable extensions'),
    '#description' => t('Extensions include many extras for configuring and styling your site and theme such as fonts, title styles, image alignment and captions, metatags &amp; touch icons for mobile and much more. Extensions can be enabled or disabled individually, so you only load what you need.'),
    '#default_value' => at_get_setting('enable_extensions'),
  );
