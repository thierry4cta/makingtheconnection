<header class="clearfix" role="banner">

  <?php if ($linked_site_logo): ?>
    <div id="logo"><?php print $linked_site_logo; ?></div>
  <?php endif; ?>

  <?php if ($site_name || $site_slogan): ?>
    <hgroup<?php if (!$site_slogan && $hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>>
      <?php if ($site_name): ?>
        <h1 id="site-name"<?php if ($hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>><?php print $site_name; ?></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
      <?php endif; ?>
    </hgroup>
  <?php endif; ?>

</header>
