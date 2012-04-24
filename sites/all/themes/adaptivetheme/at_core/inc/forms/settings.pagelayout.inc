<?php

  // Get an array of device groups with option values
  $device_group_options = responsive_page_layouts_device_group_options($theme_name);

  // Assign $options for each device group
  foreach ($device_group_options as $device_group => $options) {

    // About here we need to call a custom sort function, this is what we got for now
    sort($options, SORT_NUMERIC);

    foreach ($options as $option) {
      if ($device_group === 'bigscreen') {
        $bigscreen_options[$option] = drupal_ucfirst(str_replace('_', ' ', $option)); // human readable option names for accessibility
      }
      if ($device_group === 'tablet_landscape') {
        $tablet_landscape_options[$option] = drupal_ucfirst(str_replace('_', ' ', $option));
      }
      if ($device_group === 'tablet_portrait') {
        $tablet_portrait_options[$option] = drupal_ucfirst(str_replace('_', ' ', $option));
      }
      if ($device_group === 'smartphone_landscape') {
        $smartphone_landscape_options[$option] = drupal_ucfirst(str_replace('_', ' ', $option));
      }
    }
  }

  // Load css for the layout sprite icons
  $page_layout_css_files = responsive_plugins_admin_css($theme_name, $plugin_type = 'page_layout');
  foreach ($page_layout_css_files as $filepath) {
    if (file_exists($filepath)) {
      $page_layout_css['css'][] = array('type' => 'file', 'data' => $filepath, 'weight' => 100);
    }
  }

  // Set a message for when responsive layout is turned off
  $disable_message = t('<p>The responsive layout is disabled, only the Standard layout is now used.</p><p>To re-enable uncheck the "Disable responsive layout and styles" checkbox under the "Settings" tab.</p>');

  // Bigscreen (standard-layout)
  $form['at-layout']['bigscreen'] = array(
    '#type' => 'fieldset',
    '#title' => t('Standard Layout'),
    '#description' => t('<h3>Standard Layout</h3><p>The standard layout is for desktops, laptops and other large screen devices.'),
    '#attached' => $page_layout_css,
    '#attributes' => array(
      'class' => array('at-layout-form'),
    ),
  );
  $form['at-layout']['bigscreen']['bigscreen-layout-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose sidebar layout'),
  );
  $form['at-layout']['bigscreen']['bigscreen-layout-wrapper']['bigscreen_layout'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Choose sidebar positions</strong>'),
    '#default_value' => str_replace('-', '_', at_get_setting('bigscreen_layout')), // avoid "illigal choice" errors in 7.x-2.x sub-themes.
    '#options' => $bigscreen_options,
  );
  $form['at-layout']['bigscreen']['bigscreen-sidebar-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set sidebar widths'),
    '#description' => t('<strong>Set the width of each sidebar</strong>'),
  );
  $form['at-layout']['bigscreen']['bigscreen-sidebar-wrapper']['bigscreen_sidebar_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('bigscreen_sidebar_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['bigscreen']['bigscreen-sidebar-wrapper']['bigscreen_sidebar_first'] = array(
    '#type' => 'textfield',
    '#title' => t('First sidebar'),
    '#default_value' => at_get_setting('bigscreen_sidebar_first'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['bigscreen']['bigscreen-sidebar-wrapper']['bigscreen_sidebar_second'] = array(
    '#type' => 'textfield',
    '#title' => t('Second sidebar'),
    '#default_value' => at_get_setting('bigscreen_sidebar_second'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['bigscreen']['bigscreen-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set the page width'),
    '#description' => t('<strong>Set the page width</strong>'),
  );
  $form['at-layout']['bigscreen']['bigscreen-width-wrapper']['bigscreen_page_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('bigscreen_page_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['bigscreen']['bigscreen-width-wrapper']['bigscreen_page_width'] = array(
    '#type'  => 'textfield',
    '#title' => t('Page width'),
    '#default_value' => at_get_setting('bigscreen_page_width'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['bigscreen']['bigscreen-maxwidth-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set a max width'),
    '#states' => array(
      'visible' => array('select[name="bigscreen_page_unit"]' => array('value' => '%')),
    ),
  );
  $form['at-layout']['bigscreen']['bigscreen-maxwidth-wrapper']['bigscreen_set_max_width'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set a max width'),
    '#default_value' => at_get_setting('bigscreen_set_max_width'),
  );
  $form['at-layout']['bigscreen']['bigscreen-maxwidth-wrapper']['bigscreen_max_width_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('bigscreen_max_width_unit'),
    '#options' => array(
      'px' => 'px',
      'em' => 'em',
    ),
    '#states' => array(
      'visible' => array('input[name="bigscreen_set_max_width"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['bigscreen']['bigscreen-maxwidth-wrapper']['bigscreen_max_width'] = array(
    '#type'  => 'textfield',
    '#title' => t('Max width'),
    '#default_value' => at_get_setting('bigscreen_max_width'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#states' => array(
      'visible' => array('input[name="bigscreen_set_max_width"]' => array('checked' => TRUE)),
      'required' => array('input[name="bigscreen_set_max_width"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['bigscreen']['media-queries-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Standard Screen Media Queries'),
    '#weight' => 1,
    '#attributes' => array(
      'class' => array('at-media-queries'),
    ),
  );
  $form['at-layout']['bigscreen']['media-queries-wrapper']['bigscreen_media_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Media query for this layout'),
    '#default_value' => at_get_setting('bigscreen_media_query'),
    '#description' => t('Do not include @media, its included automatically.'),
    '#field_prefix' => '@media',
    '#size' => 100,
    '#required' => TRUE,
  );
  // Tablet
  $form['at-layout']['tablet'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tablet Layout'),
    '#description' => t('<h3>Tablet Layout</h3><p>Tablet devices such as iPad have two orientations - landscape and portrait. You can configure a different layout for each orientation.</p>'),
    '#attributes' => array(
      'class' => array('at-layout-form'),
    ),
  );
  // Disabled message
  if(at_get_setting('disable_responsive_styles') === 1) {
    $form['at-layout']['tablet']['disabled'] = array(
      '#markup' => '<div class="messages warning">'. $disable_message .'</div>',
    );
  }
  // Tablet landscape
  $form['at-layout']['tablet']['landscape'] = array(
    '#type' => 'fieldset',
    '#title' => t('Landscape'),
    '#description' => t('<h4>Landscape tablet</h4>'),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-layout-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose sidebar layout'),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-layout-wrapper']['tablet_landscape_layout'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Choose sidebar positions</strong>'),
    '#default_value' => str_replace('-', '_', at_get_setting('tablet_landscape_layout')),
    '#options' => $tablet_landscape_options,
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-sidebar-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set sidebar widths'),
    '#description' => t('<strong>Set the width of each sidebar</strong>'),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-sidebar-width-wrapper']['tablet_landscape_sidebar_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('tablet_landscape_sidebar_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-sidebar-width-wrapper']['tablet_landscape_sidebar_first'] = array(
    '#type' => 'textfield',
    '#title' => t('First sidebar'),
    '#default_value' => at_get_setting('tablet_landscape_sidebar_first'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-sidebar-width-wrapper']['tablet_landscape_sidebar_second'] = array(
    '#type' => 'textfield',
    '#title' => t('Second sidebar'),
    '#default_value' => at_get_setting('tablet_landscape_sidebar_second'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
    '#states' => array(
      'invisible' => array(
        array('input[name="tablet_landscape_layout"]' => array('value' => 'two_sidebars_left_stack')),
        array('input[name="tablet_landscape_layout"]' => array('value' => 'two_sidebars_right_stack')),
      ),
    ),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-page-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set the page width'),
    '#description' => t('<strong>Set the page width</strong>'),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-page-width-wrapper']['tablet_landscape_page_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('tablet_landscape_page_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-page-width-wrapper']['tablet_landscape_page_width'] = array(
    '#type'  => 'textfield',
    '#title' => t('Page width'),
    '#default_value' => at_get_setting('tablet_landscape_page_width'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-media-queries-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tablet Landscape Media Queries'),
    '#weight' => 1,
    '#attributes' => array(
      'class' => array(
        'at-media-queries',
      ),
    ),
  );
  $form['at-layout']['tablet']['landscape']['tablet-landscape-media-queries-wrapper']['tablet_landscape_media_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Media query for this layout'),
    '#default_value' => at_get_setting('tablet_landscape_media_query'),
    '#description' => t('Do not include @media, its included automatically.'),
    '#field_prefix' => '@media',
    '#size' => 100,
    '#required' => TRUE,
  );
  // Tablet portrait
  $form['at-layout']['tablet']['portrait'] = array(
    '#type' => 'fieldset',
    '#title' => t('Portrait'),
    '#description' => t('<h4>Portrait tablet</h4>'),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-layout-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose sidebar layout'),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-layout-wrapper']['tablet_portrait_layout'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Choose sidebar positions</strong>'),
    '#default_value' => str_replace('-', '_', at_get_setting('tablet_portrait_layout')),
    '#options' => $tablet_portrait_options,
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-sidebar-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set sidebar widths'),
    '#description' => t('<strong>Set the width of each sidebar</strong>'),
    '#states' => array(
      'invisible' => array('input[name="tablet_portrait_layout"]' => array('value' => 'one-col-stack')),
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-sidebar-width-wrapper']['tablet_portrait_sidebar_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('tablet_portrait_sidebar_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-sidebar-width-wrapper']['tablet_portrait_sidebar_first'] = array(
    '#type' => 'textfield',
    '#title' => t('First sidebar'),
    '#default_value' => at_get_setting('tablet_portrait_sidebar_first'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-sidebar-width-wrapper']['tablet_portrait_sidebar_second'] = array(
    '#type' => 'textfield',
    '#title' => t('Second sidebar'),
    '#default_value' => at_get_setting('tablet_portrait_sidebar_second'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
    '#states' => array(
      'invisible' => array(
        array('input[name="tablet_portrait_layout"]' => array('value' => 'two_sidebars_left_stack')),
        array('input[name="tablet_portrait_layout"]' => array('value' => 'two_sidebars_right_stack')),
      ),
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-page-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set the page width'),
    '#description' => t('<strong>Set the page width</strong>'),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-page-width-wrapper']['tablet_portrait_page_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('tablet_portrait_page_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-page-width-wrapper']['tablet_portrait_page_width'] = array(
    '#type'  => 'textfield',
    '#title' => t('Page width'),
    '#default_value' => at_get_setting('tablet_portrait_page_width'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#required' => TRUE,
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-media-queries-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tablet Portrait Media Queries'),
    '#weight' => 1,
    '#attributes' => array(
      'class' => array('at-media-queries'),
    ),
  );
  $form['at-layout']['tablet']['portrait']['tablet-portrait-media-queries-wrapper']['tablet_portrait_media_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Media query for this layout'),
    '#default_value' => at_get_setting('tablet_portrait_media_query'),
    '#description' => t('Do not include @media, its included automatically.'),
    '#field_prefix' => '@media',
    '#size' => 100,
    '#required' => TRUE,
  );

  // Smartphone
  $form['at-layout']['smartphone'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smartphone Layout'),
    '#description' => t('<h3>Smartphone Layout</h3><p>Smartphone devices such as iPhone, Android and Windows phones have two orientations - landscape and portrait. You can configure a layout for landscape orientation only - portrait orientation always displays in one column with sidebars stacked below the main content.</p>'),
    '#attributes' => array(
      'class' => array('at-layout-form'),
    ),
  );
  // Disabled message
  if(at_get_setting('disable_responsive_styles') === 1) {
    $form['at-layout']['smartphone']['disabled'] = array(
      '#markup' => '<div class="messages warning">'. $disable_message .'</div>',
    );
  }
  // Smartphone landscape
  $form['at-layout']['smartphone']['landscape'] = array(
    '#type' => 'fieldset',
    '#title' => t('Landscape'),
    '#description' => t('<h4>Landscape smartphone</h4>'),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-layout-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose sidebar layout'),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-layout-wrapper']['smartphone_landscape_layout'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Choose sidebar positions</strong>'),
    '#default_value' => str_replace('-', '_', at_get_setting('smartphone_landscape_layout')),
    '#options' => $smartphone_landscape_options,
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-sidebar-width-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set sidebar widths'),
    '#description' => t('<strong>Set the width of each sidebar</strong>'),
    '#states' => array(
      '!visible' => array('input[name="smartphone_landscape_layout"]' => array('value' => 'one-col-stack')),
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-sidebar-width-wrapper']['smartphone_landscape_sidebar_unit'] = array(
    '#type' => 'select',
    '#title' => t('Unit'),
    '#default_value' => at_get_setting('smartphone_landscape_sidebar_unit'),
    '#options' => array(
      'px' => 'px',
      '%' => '%',
      'em' => 'em',
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-sidebar-width-wrapper']['smartphone_landscape_sidebar_first'] = array(
    '#type' => 'textfield',
    '#title' => t('First sidebar'),
    '#default_value' => at_get_setting('smartphone_landscape_sidebar_first'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#states' => array(
      'required' => array('input[id="edit-smartphone-landscape-layout-one-col-vert"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-sidebar-width-wrapper']['smartphone_landscape_sidebar_second'] = array(
    '#type' => 'textfield',
    '#title' => t('Second sidebar'),
    '#default_value' => at_get_setting('smartphone_landscape_sidebar_second'),
    '#size' => 4,
    '#maxlenght' => 4,
    '#states' => array(
      'required' => array('input[id="edit-smartphone-landscape-layout-one-col-vert"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-media-queries-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smartphone Landscape Media Queries'),
    '#weight' => 1,
    '#attributes' => array(
      'class' => array('at-media-queries'),
    ),
  );
  $form['at-layout']['smartphone']['landscape']['smartphone-landscape-media-queries-wrapper']['smartphone_landscape_media_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Media query for this layout'),
    '#default_value' => at_get_setting('smartphone_landscape_media_query'),
    '#description' => t('Do not include @media, its included automatically.'),
    '#field_prefix' => '@media',
    '#size' => 100,
    '#required' => TRUE,
  );
  // Pass hidden values to the sumbit function, these values are required but the user can't change them via the UI, muwhawawawah...
  $form['at-layout']['smartphone']['landscape']['hidden']['smartphone_landscape_page_width'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_landscape_page_width'),
  );
  $form['at-layout']['smartphone']['landscape']['hidden']['smartphone_landscape_page_unit'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_landscape_page_unit'),
  );
  // Smartphone portrait
  $form['at-layout']['smartphone']['portrait'] = array(
    '#type' => 'fieldset',
    '#title' => t('Portrait'),
    '#description' => t('<h4>Portrait smartphone</h4><div class="smartphone-portrait-layout">One column</div><p>The smartphone portrait layout always displays in one column with sidebars stacked horizontally below the main content. All widths are always 100%.</p>'),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );
  $form['at-layout']['smartphone']['portrait']['smartphone-portrait-media-queries-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smartphone Portrait Media Queries'),
    '#weight' => 1,
    '#attributes' => array(
      'class' => array('at-media-queries'),
    ),
  );
  $form['at-layout']['smartphone']['portrait']['smartphone-portrait-media-queries-wrapper']['smartphone_portrait_media_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Media query for this layout'),
    '#default_value' => at_get_setting('smartphone_portrait_media_query'),
    '#description' => t('Do not include @media, its included automatically.'),
    '#field_prefix' => '@media',
    '#size' => 100,
  );
  // Pass hidden values to the sumbit function, these values are required but the user can't change them via the UI, muwhawawawah...
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_page_width'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_portrait_page_width'),
  );
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_page_unit'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_portrait_page_unit'),
  );
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_sidebar_first'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_portrait_sidebar_first'),
  );
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_sidebar_second'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_portrait_sidebar_second'),
  );
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_sidebar_unit'] = array(
    '#type' => 'hidden',
    '#default_value' => at_get_setting('smartphone_portrait_sidebar_unit'),
  );
  $form['at-layout']['smartphone']['portrait']['hidden']['smartphone_portrait_layout'] = array(
    '#type' => 'hidden',
    '#default_value' => str_replace('-', '_', at_get_setting('smartphone_portrait_layout')),
  );
