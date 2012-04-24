<?php

  // Modify HTML Output
  $form['at']['modify-output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Markup Overrides'),
    '#weight' => -20,
  );

  // Design
  $form['at']['modify-output']['design'] = array(
    '#type' => 'fieldset',
    '#title' => t('Design'),
    '#description' => t('<h3>Design</h3>'),
  );

  // Adjust gutter width
  $form['at']['modify-output']['design']['global_gutter_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Set gutter width: '),
    '#size' => 2,
    '#maxlength' => 2,
    '#field_suffix' => 'px',
    '#description' => t('Gutters are set using margin-left and margin-right. This will override the default 10px margins set in <code>global.page.css</code>.'),
    '#default_value' => at_get_setting('global_gutter_width'),
  );

  // Use the page full width wrappers template
  $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use page--full-width-wrappers.tpl.php by default'),
    '#description' => t('This setting will load a page template will full width DIV wrappers - perfect for designs with 100% width sections, header or footer. Note that if you choose to use other page template suggestions you should use copies of page--full-width-wrappers.tpl.php, you will find this in adaptivetheme/at-core/templates.'),
    '#default_value' => at_get_setting('page_full_width_wrappers'),
  );

  // Add spans to theme_links
  $form['at']['modify-output']['design']['menu_item_span_elements'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wrap menu item text in SPAN tags - useful for certain theme or design related techniques'),
    '#description' => t('Note: this does not work for <a href="!link" target="_blank">Superfish menus</a>, which includes its own feature for doing this.', array('!link' => 'http://drupal.org/project/superfish')),
    '#default_value' => at_get_setting('menu_item_span_elements'),
  );

  // Extra CSS Classes
  $form['at']['modify-output']['extra-classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra Classes'),
    '#description' => t('<h3>Extra CSS Classes</h3>'),
  );

  // Page
  $form['at']['modify-output']['extra-classes']['extra_page_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page classes'),
    '#description' => t('page-path, add/edit/delete (for workflow states), content type classes, section classes and a language class (i18n)'),
    '#default_value' => at_get_setting('extra_page_classes'),
  );

  // Node
  $form['at']['modify-output']['extra-classes']['extra_article_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node classes'),
    '#description' => t('promoted, sticky, preview, language, odd/even classes, user picture handling, and build mode classes'),
    '#default_value' => at_get_setting('extra_article_classes'),
  );

  // Comment
  $form['at']['modify-output']['extra-classes']['extra_comment_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Comment classes '),
    '#description' => t('anonymous, author, viewer, new, odd/even classes and classes for hidden titles, user picture and signature handling'),
    '#default_value' => at_get_setting('extra_comment_classes'),
  );

  // Block
  $form['at']['modify-output']['extra-classes']['extra_block_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Blocks classes'),
    '#description' => t('odd/even (zebra classes), block region, delta and block count classes'),
    '#default_value' => at_get_setting('extra_block_classes'),
  );

  // Menu
  $form['at']['modify-output']['extra-classes']['extra_menu_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Menus classes'),
    '#description' =>  t('menu link ID (mlid) and menu level (depth)'),
    '#default_value' => at_get_setting('extra_menu_classes'),
  );

  // Item lists
  $form['at']['modify-output']['extra-classes']['extra_item_list_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Item-lists classes'),
    '#description' => t('first, last and odd/even (zebra classes)'),
    '#default_value' => at_get_setting('extra_item_list_classes'),
  );

  // Hide or Remove
  $form['at']['modify-output']['hide-remove'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hide or Remove'),
    '#description' => t('<h3>Hide or Remove</h3>'),
  );

  // Hide comment title
  $form['at']['modify-output']['hide-remove']['comments_hide_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the comment title'),
    '#default_value' => at_get_setting('comments_hide_title'),
    '#description' => t('Checking this setting will hide comment titles using element-invisible. Hiding rather than removing titles maintains accessibility and semantic structure while not showing titles to sighted users.'),
  );

  // Hide RSS icons
  $form['at']['modify-output']['hide-remove']['feed_icons_hide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove RSS feed icons'),
    '#default_value' => at_get_setting('feed_icons_hide'),
    '#description' => t('Checking this setting will remove RSS feed icons. This will not affect the Syndicate block icon.'),
  );

  // Unset block system main front
  $form['at']['modify-output']['hide-remove']['unset_block_system_main_front'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not display the Main content block on the front page'),
    '#default_value' => at_get_setting('unset_block_system_main_front'),
    '#description' => t('Checking this setting will remove the Main content block from the front page only - useful for removing the welcome message and allowing use of another block.'),
  );

  // Accessibility
  $form['at']['modify-output']['a11y'] = array(
    '#type' => 'fieldset',
    '#title' => t('Accessibility'),
    '#description' => t('<h3>Accessibility</h3>'),
  );

  // Use extra fieldsets in advanced serach form
  $form['at']['modify-output']['a11y']['adv_search_extra_fieldsets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use extra fieldset wrappers in the advanced search form'),
    '#default_value' => at_get_setting('adv_search_extra_fieldsets'),
    '#description' => t('The problem with Drupals standard Advanced search form is that each criterion group is wrapped in a DIV, whereas it should use fieldsets. Turning this on may cause issues with modules that modify the search form such as Search Config.'),
  );

  // Skip link target
  $form['at']['modify-output']['a11y']['skip_link_target'] = array(
    '#type' => 'textfield',
    '#title' => t('Skip to navigation target ID'),
    '#description' => t('If your main content is not in the Main Content region you can change the skip link target ID to match.'),
    '#default_value' => at_get_setting('skip_link_target'),
  );
