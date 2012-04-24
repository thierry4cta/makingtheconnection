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

; 4 col
regions[four_first]  = 4col Gpanel - 1
regions[four_second] = 4col Gpanel - 2
regions[four_third]  = 4col Gpanel - 3
regions[four_fourth] = 4col Gpanel - 4

 */
?>
<!-- Four column Gpanel -->
<?php if (
  $page['four_first'] ||
  $page['four_second'] ||
  $page['four_third'] ||
  $page['four_fourth']
  ): ?>
  <div class="at-panel gpanel panel-display four-4x25 clearfix">
    <div class="panel-row row-1 clearfix">
      <?php print render($page['four_first']); ?>
      <?php print render($page['four_second']); ?>
    </div>
    <div class="panel-row row-2 clearfix">  
      <?php print render($page['four_third']); ?>
      <?php print render($page['four_fourth']); ?>
    </div>
  </div>
<?php endif; ?>
