<?php if ($pane_prefix): ?>
  <?php print $pane_prefix; ?>
<?php endif; ?>
<?php $tag = $title ? 'section' : 'div'; ?>
<<?php print $tag; ?> class="<?php print $classes; ?>" <?php print $id; ?>>
  <?php if ($admin_links): ?>
    <?php print $admin_links; ?>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($feeds): ?>
    <div class="feed"><?php print $feeds; ?></div>
  <?php endif; ?>

  <div class="pane-content">
    <?php print render($content); ?>
  </div>

  <?php if ($links): ?>
    <nav class="links clearfix"><?php print $links; ?></nav>
  <?php endif; ?>

  <?php if ($more): ?>
    <div class="more-link"><?php print $more; ?></div>
  <?php endif; ?>

</<?php print $tag; ?>>
<?php if ($pane_suffix): ?>
  <?php print $pane_suffix; ?>
<?php endif; ?>
