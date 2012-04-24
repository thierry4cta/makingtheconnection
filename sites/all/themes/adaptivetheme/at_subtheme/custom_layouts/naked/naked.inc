<?php
/**
 * @file
 * Implimentation of an Adaptivetheme Page Layout plugin
 */
function naked() {
  $page_layout['naked'] = array(
    'title' => t('Naked'),
    'category' => t('AT Subtheme Custom Page Layout'),
    'method' => 'naked',
    'type'      => 'page_layout',
    'device_groups' => array(
      'bigscreen',
      'tablet_landscape',
      'tablet_portrait',
      'smartphone_landscape',
    ),
  );
  return $page_layout;
}

function naked_layout($sidebar_first, $sidebar_second, $sidebar_unit){
  $styles = array();
  $output = '';
  $styles[] = '/* Nothing to output, this style is naked! */';
  $output = implode('', $styles);
  return $output;
}