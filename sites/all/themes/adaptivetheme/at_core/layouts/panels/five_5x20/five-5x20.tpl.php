<?php
/**
 * @file
 * Adativetheme implementation to present a Panels layout.
 *
 * Available variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 * - $css_id: unique id if present.
 * - $panel_prefix: prints a wrapper when this template is used in certain context,
 *   such as when rendered by Display Suite or other module - the wrapper is
 *   added by Adaptivetheme in the appropriate process function.
 * - $panel_suffix: closing element for the $prefix.
 *
 * @see adaptivetheme_preprocess_five_5x20()
 * @see adaptivetheme_preprocess_node()
 * @see adaptivetheme_process_node()
 */
?>
<?php print $panel_prefix; ?>
<div class="at-panel panel-display five-5x20 clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-row row-1 clearfix">
    <div class="region region-five-first">
      <div class="region-inner clearfix">
        <?php print $content['five_first']; ?>
      </div>
    </div>
    <div class="region region-five-second">
      <div class="region-inner clearfix">
        <?php print $content['five_second']; ?>
      </div>
    </div>
  </div>
  <div class="panel-row row-2 clearfix">
    <div class="region region-five-third">
      <div class="region-inner clearfix">
        <?php print $content['five_third']; ?>
      </div>
    </div>
    <div class="region region-five-fourth">
      <div class="region-inner clearfix">
        <?php print $content['five_fourth']; ?>
      </div>
    </div>
    <div class="region region-five-fifth">
      <div class="region-inner clearfix">
        <?php print $content['five_fifth']; ?>
      </div>
    </div>
  </div>
</div>
<?php print $panel_suffix; ?>
