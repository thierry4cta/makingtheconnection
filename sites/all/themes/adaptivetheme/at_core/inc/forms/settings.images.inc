<?php

  // Image styles
  $form['at']['images'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image Settings'),
    '#description' => '<h3>Image Settings</h3><p>Set alignment for image-field images on full and teaser view, and enable captions.',
    '#weight' => -80,
  );

  // Alignment
  $form['at']['images']['alignment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image Alignment'),
  );

  // Full
  $form['at']['images']['alignment']['image_alignment'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Alignment - full view</strong>'),
    '#default_value' => at_get_setting('image_alignment'),
    '#options' => array(
      'ia-n' => t('None'),
      'ia-l' => t('Left'),
      'ia-c' => t('Center'),
      'ia-r' => t('Right'),
    ),
  );

  // Teaser
  $form['at']['images']['alignment']['image_alignment_teaser'] = array(
    '#type' => 'radios',
    '#title' => t('<strong>Alignment - teaser view</strong>'),
    '#default_value' => at_get_setting('image_alignment_teaser'),
    '#description' => t('This will only affect images added using an image-field. If you use another method such as embedding images directly into text areas this will not affect those images.'),
    '#options' => array(
      'iat-n' => t('None'),
      'iat-l' => t('Left'),
      'iat-c' => t('Center'),
      'iat-r' => t('Right'),
    ),
  );

  // Captions
  $form['at']['images']['captions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image Captions'),
    '#description' => t('<strong>Display the image title as a caption</strong>'),
  );
  $form['at']['images']['captions']['image_caption_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show captions on teaser view'),
    '#default_value' => at_get_setting('image_caption_teaser'),
  );
  $form['at']['images']['captions']['image_caption_full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show captions on full view'),
    '#description' => t('Captions use the title attribute text. You must enable tiles in the field management options for your image fields.'),
    '#default_value' => at_get_setting('image_caption_full'),
  );
