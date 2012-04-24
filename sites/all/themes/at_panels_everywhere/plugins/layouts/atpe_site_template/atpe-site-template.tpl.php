<div<?php print $css_id ? " id=\"$css_id\"" : ''; ?> class="<?php print $sidebar_classes; ?>">

  <?php if (!empty($content['leaderboard'])): ?>
    <?php print render($content['leaderboard']); ?>
  <?php endif; ?>

  <?php if (!empty($content['header'])): ?>
    <header class="clearfix" role="banner">
      <?php print render($content['header']); ?>
    </header>
  <?php endif; ?>

  <?php if (!empty($content['menu_bar'])): ?>
    <?php print render($content['menu_bar']); ?>
  <?php endif; ?>

  <?php if (!empty($content['help'])): ?>
    <?php print render($content['help']); ?>
  <?php endif; ?>

  <?php if (!empty($content['secondary_content'])): ?>
    <?php print render($content['secondary_content']); ?>
  <?php endif; ?>

  <div id="columns">
    <div class="columns-inner clearfix">
      <div id="content-column" role="main">
        <div class="content-inner">

          <?php if (!empty($content['highlighted'])): ?>
            <?php print render($content['highlighted']); ?>
          <?php endif; ?>

          <div id="content">
            <div class="region region-content content">
              <?php print render($content['content']); ?>
            </div>
          </div>

          <?php if (!empty($content['content_aside'])): ?>
            <?php print render($content['content_aside']); ?>
          <?php endif; ?>

        </div>
      </div>

      <?php if (!empty($content['sidebar_first'])): ?>
        <div class="region region-sidebar-first sidebar"><?php print render($content['sidebar_first']); ?></div>
      <?php endif; ?>

      <?php if (!empty($content['sidebar_second'])): ?>
        <div class="region region-sidebar-second sidebar"><?php print render($content['sidebar_second']); ?></div>
      <?php endif; ?>

    </div>
  </div>

  <?php if (!empty($content['tertiary_content'])): ?>
    <?php print render($content['tertiary_content']); ?>
  <?php endif; ?>

  <?php if (!empty($content['footer'])): ?>
    <footer role="contentinfo"><?php print render($content['footer']); ?></footer>
  <?php endif; ?>

</div>
