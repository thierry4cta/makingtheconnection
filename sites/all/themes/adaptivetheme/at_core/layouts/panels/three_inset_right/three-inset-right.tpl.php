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
 * @see adaptivetheme_preprocess_three_inset_right()
 * @see adaptivetheme_preprocess_node()
 * @see adaptivetheme_process_node()
 */
?>
<?php print $panel_prefix; ?>
<div class="at-panel panel-display three-inset-right clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="region region-three-inset-right-sidebar">
    <div class="region-inner clearfix">
      <?php print $content['three_inset_right_sidebar']; ?>
    </div>
  </div>
  <div class="inset-wrapper clearfix">
    <?php if ($content['three_inset_right_top']): ?>
      <div class="region region-three-inset-right-top region-conditional-stack">
        <div class="region-inner clearfix">
          <?php print $content['three_inset_right_top']; ?>
        </div>
      </div>
    <?php endif; ?>

    <div class="region region-three-inset-right-middle">
      <div class="region-inner clearfix">
        <?php print $content['three_inset_right_middle']; ?>
      </div>
    </div>
    <div class="region region-three-inset-right-inset">
      <div class="region-inner clearfix">
        <?php print $content['three_inset_right_inset']; ?>
      </div>
    </div>
    <?php if ($content['three_inset_right_bottom']): ?>
      <div class="region region-three-inset-right-bottom region-conditional-stack">
        <div class="region-inner clearfix">
          <?php print $content['three_inset_right_bottom']; ?>
        </div>
      </div>
    <?php endif; ?>
  </div>
</div>
<?php print $panel_suffix; ?>
