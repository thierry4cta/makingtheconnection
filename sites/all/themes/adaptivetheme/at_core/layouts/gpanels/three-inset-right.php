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
regions[threecol_inset_right_sidebar] = 3 col Inset right - sidebar
regions[threecol_inset_right_top]     = 3 col Inset right - top
regions[threecol_inset_right_middle]  = 3 col Inset right - middle
regions[threecol_inset_right_inset]   = 3 col Inset right - inset
regions[threecol_inset_right_bottom]  = 3 col Inset right - bottom

 */
?>
<!-- Three col inset right -->
<?php if (
  $page['threecol_inset_right_sidebar'] ||
  $page['threecol_inset_right_top'] || 
  $page['threecol_inset_right_middle'] ||
  $page['threecol_inset_right_inset'] ||
  $page['threecol_inset_right_bottom']
  ): ?>
<div class="at-panel gpanel panel-display three-inset-right clearfix">
  <?php print $content['threecol_inset_right_sidebar']; ?>
  <div class="inset-wrapper clearfix">
    <?php print $content['threecol_inset_right_top']; ?>
    <?php print $content['threecol_inset_right_middle']; ?>
    <?php print $content['threecol_inset_right_inset']; ?>
    <?php print $content['threecol_inset_right_bottom']; ?>
  </div>
</div>
