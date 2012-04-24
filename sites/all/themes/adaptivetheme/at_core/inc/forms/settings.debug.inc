<?php

  // DEBUG
  $form['at-layout']['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug'),
  );
  $form['at-layout']['debug']['debug-layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debuggers'),
    '#description' => t('<h3>Debuggers</h3>'),
  );

  // Highlight regions
  $form['at-layout']['debug']['debug-layout']['expose_regions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlight regions'),
    '#default_value' => at_get_setting('expose_regions'),
  );

  // Load all panels
  $form['at-layout']['debug']['debug-layout']['load_all_panels'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace the front page with panels_test.html - useful for studying and debugging Responsive Panels'),
    '#default_value' => at_get_setting('load_all_panels'),
  );

  // Window size bookmarklet
  $form['at-layout']['debug']['debug-layout']['show_window_size'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show window size - appears in the bottom right corner'),
    '#default_value' => at_get_setting('show_window_size'),
  );

  // Version test
  $form['at-layout']['debug']['debug-layout']['atcore_version_test'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sub-theme compatibility test'),
    '#default_value' => at_get_setting('atcore_version_test'),
  );

  // All media queries, wow this is kinda fugly, did I really do this, I must
  // have been out with mortendk at dcamp or something...
  $queries = '';
  $mq = array();
  $mq[] =  '/* Smartphone portrait */' . "\n" . '@media ' . at_get_setting('smartphone_portrait_media_query') . ' {' . "\n" . '}';
  $mq[] =  '/* Smartphone landscape */' . "\n" . '@media ' . at_get_setting('smartphone_landscape_media_query') . ' {' . "\n" . '}';
  $mq[] =  '/* Tablet portrait */' . "\n" . '@media ' . at_get_setting('tablet_portrait_media_query') . ' {' . "\n" . '}';
  $mq[] =  '/* Tablet landscape */' . "\n" . '@media ' . at_get_setting('tablet_landscape_media_query') . ' {' . "\n" . '}';
  $mq[] =  '/* Standard layout */' . "\n" . '@media ' . at_get_setting('bigscreen_media_query') . ' {' . "\n" . '}';
  $queries = implode("\n\n", $mq);
  $form['at-layout']['debug']['mediaqueries'] = array(
    '#type' => 'fieldset',
    '#title' => t('<h3>All Media Queries - Copy Only!</h3>'),
    '#description' => t('<h3>All Media Queries - Copy Only</h3><p>These are the media queries currently being used by your theme. This is provided so you may save a backup copy for reference. Do not enter anything here - this is display only!</p>'),
  );
  $form['at-layout']['debug']['mediaqueries']['check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the text field so I can copy this now'),
  );
  $form['at-layout']['debug']['mediaqueries']['output'] = array(
    '#type' => 'textarea',
    '#rows' => 18,
    '#default_value' => $queries ? $queries : '',
    '#states' => array(
      'disabled' => array('input[name="check"]' => array('checked' => FALSE)),
    ),
  );
