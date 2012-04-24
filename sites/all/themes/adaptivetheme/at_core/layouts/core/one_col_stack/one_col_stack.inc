<?php
/**
 * Implimentation of a Page Layout Plugin for Adaptivetheme.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function one_col_stack() {
  $page_layout['one_col_stack'] = array(
    'title'    => t('One Column Stacked'),
    'category' => t('AT Core layout'),
    'method'   => 'one_col_stack',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_portrait',
      'smartphone_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the one_col_stack layout.
 * Note: this is the only layout for smartphone portrait, and for mobile first.
 * All columns and regions are 100% width, stacked.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function one_col_stack_layout($sidebar_first, $sidebar_second, $sidebar_unit) {
  $styles = <<<EOF
.two-sidebars .content-inner,.one-sidebar .content-inner,.region-sidebar-first,.region-sidebar-second {margin-left: 0; margin-right: 0}
.region-sidebar-first,.region-sidebar-second,.region-sidebar-first .block,.region-sidebar-second .block {width: 100%}
.region-sidebar-second {width: 100%}
.content-inner,.region-sidebar-first,.region-sidebar-second {float: none}
.region-sidebar-first,.region-sidebar-second {clear: both}
EOF;

  return $styles;
}
