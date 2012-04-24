<?php

  // Login block options. There is also a slide-down block option, but I have never added it.
  $form['at']['login-block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login Block'),
    '#description' => t('<h3>Login Block Options</h3>'),
    '#weight' => -50,
  );
  $form['at']['login-block']['hlb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login Block'),
  );

  // Horizonal login block
  $form['at']['login-block']['hlb']['horizontal_login_block'] = array(
    '#type' => 'checkbox',
    '#title' => t('Horizontal Login Block'),
    '#default_value' => at_get_setting('horizontal_login_block'),
    '#description' => t('Checking this setting will enable a horizontal style login block (all elements on one line). Note that if you are using OpenID this does not work well and you will need a more sophistocated approach than can be provided here.'),
  );
