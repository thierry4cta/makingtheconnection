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

; 3 col Inset Right
regions[threecol_inset_left_sidebar] = 3 col Inset left - sidebar
regions[threecol_inset_left_top]     = 3 col Inset left - top
regions[threecol_inset_left_middle]  = 3 col Inset left - middle
regions[threecol_inset_left_inset]   = 3 col Inset left - inset
regions[threecol_inset_left_bottom]  = 3 col Inset left - bottom

 */
?>
<!-- Three col inset left -->
<?php if (
  $page['threecol_inset_left_sidebar'] ||
  $page['threecol_inset_left_top'] || 
  $page['threecol_inset_left_middle'] ||
  $page['threecol_inset_left_inset'] ||
  $page['threecol_inset_left_bottom']
  ): ?>
<div class="at-panel gpanel panel-display three-inset-left clearfix">
  <?php print $content['threecol_inset_left_sidebar']; ?>
  <div class="inset-wrapper clearfix">
    <?php print $content['threecol_inset_left_top']; ?>
    <?php print $content['threecol_inset_left_middle']; ?>
    <?php print $content['threecol_inset_left_inset']; ?>
    <?php print $content['threecol_inset_left_bottom']; ?>
  </div>
</div>