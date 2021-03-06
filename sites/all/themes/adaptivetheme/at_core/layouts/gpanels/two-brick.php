<?php
/**
 * Gpanels are drop in multi-column snippets for displaying blocks.
 * Most Gpanels are stacked, meaning they have top and bottom regions
 * by default, however you do not need to use them. You should always
 * use all the horizonal regions or you might experience layout issues.
 *
 * How to use:
 * 1. Copy and paste the code snippet into your page.tpl.php file.
 * 2. Copy and paste the region definitions to your themes .info file.
 * 3. Clear the cache (in Performance settings) to refresh the theme registry.

Region Deinitions:

; 2 col 2x50
regions[two_brick_top]         = 2 col Brick top
regions[two_brick_left_above]  = 2 col Brick left above
regions[two_brick_right_above] = 2 col Brick right above
regions[two_brick_middle]      = 2 col Brick middle
regions[two_brick_left_below]  = 2 col Brick left below
regions[two_brick_right_below] = 2 col Brick right below
regions[two_brick_bottom]      = 2 col Brick bottom

 */
?>
<!-- Two column brick -->
<?php if (
  $page['two_brick_top'] ||
  $page['two_brick_left_above'] || 
  $page['two_brick_right_above'] ||
  $page['two_brick_middle'] ||
  $page['two_brick_left_below'] ||
  $page['two_brick_right_below'] ||
  $page['two_brick_bottom']
  ): ?>
<div class="at-panel gpanel panel-display two-brick clearfix">
  <?php print render($page['two_brick_top']); ?>
  <div class="panel-row row-1 clearfix">
    <?php print render($page['two_brick_left_above']); ?>
    <?php print render($page['two_brick_right_above']); ?>
  </div>
  <?php print render($page['two_brick_middle']); ?>
  <div class="panel-row row-2 clearfix">
    <?php print render($page['two_brick_left_below']); ?>
    <?php print render($page['two_brick_right_below']); ?>
  </div>
  <?php print render($page['two_brick_bottom']); ?>
</div>
<?php endif; ?>
