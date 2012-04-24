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

; 3 col 50-25-25
regions[three_50_25_25_top]    = 50-25-25 Gpanel top
regions[three_50_25_25_first]  = 50-25-25 Gpanel left
regions[three_50_25_25_second] = 50-25-25 Gpanel center
regions[three_50_25_25_third]  = 50-25-25 Gpanel right
regions[three_50_25_25_bottom] = 50-25-25 Gpanel bottom

 */
?>
<!-- Three column 50-25-25 -->
<?php if (
  $page['three_50_25_25_top'] || 
  $page['three_50_25_25_first'] || 
  $page['three_50_25_25_second'] || 
  $page['three_50_25_25_third'] ||
  $page['three_50_25_25_bottom']
  ): ?>
  <div class="at-panel gpanel panel-display three-50-25-25 clearfix">
    <?php print render($page['three_50_25_25_top']); ?>
    <?php print render($page['three_50_25_25_first']); ?>
    <?php print render($page['three_50_25_25_second']); ?>
    <?php print render($page['three_50_25_25_third']); ?>
    <?php print render($page['three_50_25_25_bottom']); ?>
  </div>
<?php endif; ?>
