<?php
function adaptivetheme_three_inset_left_panels_layouts() {
  $items['three_inset_left'] = array(
    'title' => t('AT Three colume inset left'),
    'category' => t('AT Responsive Panels - Inset'),
    'icon' => 'three_inset_left.png',
    'theme' => 'three_inset_left',
    'admin css' => 'three_inset_left.admin.css',
    'theme arguments' => array('id', 'content'),
    'regions' => array(
      'three_inset_left_sidebar' => t('Sidebar'),
      'three_inset_left_top'     => t('Top (conditional)'),
      'three_inset_left_middle'  => t('Middle'),
      'three_inset_left_inset'   => t('Inset'),
      'three_inset_left_bottom'  => t('Bottom (conditional)'),
    ),
    // AT
    'type' => 'inset',
    'options' => array(
      'three-inset-left' => 'default',
      'three-inset-left-wrap' => 'wrap',
      'three-inset-left-stack' => 'stack',
    ),
    'styles' => array(
      'three-inset-left' => array(
        'css' => array(
          '25' => array('.three-inset-left .region-three-inset-left-sidebar' => 'width:25%'),
          '75fl' => array('.three-inset-left .inset-wrapper' => 'width:75%;float:left'),
          '33' => array('.three-inset-left .inset-wrapper div.region-three-inset-left-inset' => 'width:33.333333%'),
          '66' => array('.three-inset-left .inset-wrapper div.region-three-inset-left-middle' => 'width:66.666666%'),
          '100' => array('.three-inset-left .inset-wrapper .region' => 'width:100%'),
        ),
      ),
      'three-inset-left-wrap' => array(
        'css' => array(
          '25' => array('.three-inset-left .region-three-inset-left-sidebar' => 'width:25%'),
          '75fl' => array('.three-inset-left .inset-wrapper' => 'width:75%;float:left'),
          'fdw' => array('.three-inset-left .inset-wrapper .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
      'three-inset-left-stack' => array(
        'css' => array(
          'fdw' => array('.three-inset-left .inset-wrapper,.three-inset-left .region' => 'float:none;display:block;width:100%;clear:both'),
        ),
      ),
    ),
  );

  return $items;
}

function template_preprocess_three_inset_left(&$vars) {
  $vars['panel_prefix'] = '';
  $vars['panel_suffix'] = '';
}
