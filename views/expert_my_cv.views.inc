<?php

$expert_data = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'expert_data'));
$generic_skills = civicrm_api3('CustomField', 'getvalue', array('name' => 'generic_skills', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));

$expert_status = civicrm_api3('CustomField', 'getvalue', array('name' => 'expert_status', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));
$expert_status_start_date = civicrm_api3('CustomField', 'getvalue', array('name' => 'expert_status_start_date', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));
$expert_status_end_date = civicrm_api3('CustomField', 'getvalue', array('name' => 'expert_status_end_date', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));
$expert_status_reason = civicrm_api3('CustomField', 'getvalue', array('name' => 'expert_status_reason', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));

$cv_in_mutation = civicrm_api3('CustomField', 'getvalue', array('name' => 'CV_in_Mutation', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));
$side_activities = civicrm_api3('CustomField', 'getvalue', array('name' => 'side_activities', 'return' => 'column_name', 'custom_group_id' => $expert_data['id']));

$expert_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Expert', 'return' => 'id'));

$view = new view();
$view->name = 'expert_my_cv';
$view->description = 'My CV of expert';
$view->tag = 'expert access';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Expert CV';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'CV';
$handler->display->display_options['css_class'] = 'pum-list-view';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_expert_mycv_get_role_ids(array('Expert'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = '';
$handler->display->display_options['fields']['display_name']['element_type'] = 'h2';
$handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Edit my CV';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'expert/my-cv-edit';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = 'Groups';
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_output'] = '<?php echo _pum_expert_mycv_get_groups(); ?>';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Expert Data: Expert status */
$handler->display->display_options['fields']['expert_status_123']['id'] = 'expert_status_123';
$handler->display->display_options['fields']['expert_status_123']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['expert_status_123']['field'] = $expert_status;
$handler->display->display_options['fields']['expert_status_123']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['expert_status_123']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['expert_status_123']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['expert_status_123']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Expert Data: Start date expert status */
$handler->display->display_options['fields']['start_date_expert_status_124']['id'] = 'start_date_expert_status_124';
$handler->display->display_options['fields']['start_date_expert_status_124']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['start_date_expert_status_124']['field'] = $expert_status_start_date;
$handler->display->display_options['fields']['start_date_expert_status_124']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['start_date_expert_status_124']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['start_date_expert_status_124']['date_format'] = 'custom';
$handler->display->display_options['fields']['start_date_expert_status_124']['custom_date_format'] = 'd-m-Y';
$handler->display->display_options['fields']['start_date_expert_status_124']['second_date_format'] = 'long';
$handler->display->display_options['fields']['start_date_expert_status_124']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['start_date_expert_status_124']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Expert Data: End date expert status */
$handler->display->display_options['fields']['end_date_expert_status_125']['id'] = 'end_date_expert_status_125';
$handler->display->display_options['fields']['end_date_expert_status_125']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['end_date_expert_status_125']['field'] = $expert_status_end_date;
$handler->display->display_options['fields']['end_date_expert_status_125']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['end_date_expert_status_125']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['end_date_expert_status_125']['date_format'] = 'custom';
$handler->display->display_options['fields']['end_date_expert_status_125']['custom_date_format'] = 'd-m-Y';
$handler->display->display_options['fields']['end_date_expert_status_125']['second_date_format'] = 'long';
$handler->display->display_options['fields']['end_date_expert_status_125']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['end_date_expert_status_125']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Expert Data: Reason expert status */
$handler->display->display_options['fields']['reason_expert_status_126']['id'] = 'reason_expert_status_126';
$handler->display->display_options['fields']['reason_expert_status_126']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['reason_expert_status_126']['field'] = $expert_status_reason;
$handler->display->display_options['fields']['reason_expert_status_126']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['reason_expert_status_126']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['reason_expert_status_126']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['reason_expert_status_126']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['reason_expert_status_126']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['reason_expert_status_126']['element_label_colon'] = FALSE;
/* Field: Restrictions */
$handler->display->display_options['fields']['view_restrictions']['id'] = 'view_restrictions';
$handler->display->display_options['fields']['view_restrictions']['table'] = 'views';
$handler->display->display_options['fields']['view_restrictions']['field'] = 'view';
$handler->display->display_options['fields']['view_restrictions']['ui_name'] = 'Restrictions';
$handler->display->display_options['fields']['view_restrictions']['label'] = 'Restrictions';
$handler->display->display_options['fields']['view_restrictions']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_restrictions']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_restrictions']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['view_restrictions']['view'] = 'expert_cv_restrictions';
$handler->display->display_options['fields']['view_restrictions']['arguments'] = '[id]';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_1']['id'] = 'php_1';
$handler->display->display_options['fields']['php_1']['table'] = 'views';
$handler->display->display_options['fields']['php_1']['field'] = 'php';
$handler->display->display_options['fields']['php_1']['label'] = 'Sector';
$handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_1']['php_output'] = '<?php echo _pum_expert_mycv_get_sector(); ?>';
$handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php_1']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_2']['id'] = 'php_2';
$handler->display->display_options['fields']['php_2']['table'] = 'views';
$handler->display->display_options['fields']['php_2']['field'] = 'php';
$handler->display->display_options['fields']['php_2']['label'] = 'Areas of expertise';
$handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_2']['php_output'] = '<?php echo _pum_expert_mycv_get_areas_of_expertise(); ?>';
$handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php_2']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_3']['id'] = 'php_3';
$handler->display->display_options['fields']['php_3']['table'] = 'views';
$handler->display->display_options['fields']['php_3']['field'] = 'php';
$handler->display->display_options['fields']['php_3']['label'] = 'Sector coordinator';
$handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_3']['php_output'] = '<?php echo _pum_expert_mycv_get_sector_coordinator(); ?>';
$handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php_3']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Expert Data: Generic Skills */
$handler->display->display_options['fields']['generic_skilss_568']['id'] = 'generic_skilss_568';
$handler->display->display_options['fields']['generic_skilss_568']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['generic_skilss_568']['field'] = $generic_skills;
$handler->display->display_options['fields']['generic_skilss_568']['label'] = 'Generic skills';
$handler->display->display_options['fields']['generic_skilss_568']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['generic_skilss_568']['element_label_colon'] = FALSE;
/* Field: Languages */
$handler->display->display_options['fields']['view_1']['id'] = 'view_1';
$handler->display->display_options['fields']['view_1']['table'] = 'views';
$handler->display->display_options['fields']['view_1']['field'] = 'view';
$handler->display->display_options['fields']['view_1']['ui_name'] = 'Languages';
$handler->display->display_options['fields']['view_1']['label'] = 'Languages';
$handler->display->display_options['fields']['view_1']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_1']['view'] = 'expert_cv_languages_';
$handler->display->display_options['fields']['view_1']['arguments'] = '[id]';
/* Field: CiviCRM Custom: Expert Data: CV in Mutation */
$handler->display->display_options['fields']['cv_in_mutation_383']['id'] = 'cv_in_mutation_383';
$handler->display->display_options['fields']['cv_in_mutation_383']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['cv_in_mutation_383']['field'] = $cv_in_mutation;
$handler->display->display_options['fields']['cv_in_mutation_383']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['cv_in_mutation_383']['element_label_colon'] = FALSE;
/* Field: Education */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['ui_name'] = 'Education';
$handler->display->display_options['fields']['view']['label'] = 'Education';
$handler->display->display_options['fields']['view']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view']['view'] = 'expert_cv_education_';
$handler->display->display_options['fields']['view']['arguments'] = '[id]';
/* Field: Work history */
$handler->display->display_options['fields']['view_2']['id'] = 'view_2';
$handler->display->display_options['fields']['view_2']['table'] = 'views';
$handler->display->display_options['fields']['view_2']['field'] = 'view';
$handler->display->display_options['fields']['view_2']['ui_name'] = 'Work history';
$handler->display->display_options['fields']['view_2']['label'] = 'Work history';
$handler->display->display_options['fields']['view_2']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_2']['view'] = 'expert_cv_work_experience_';
$handler->display->display_options['fields']['view_2']['arguments'] = '[id]';
/* Field: CiviCRM Custom: Expert Data: Professional affiliation and side activities */
$handler->display->display_options['fields']['professional_affiliation_and_sid_128']['id'] = 'professional_affiliation_and_sid_128';
$handler->display->display_options['fields']['professional_affiliation_and_sid_128']['table'] = $expert_data['table_name'];
$handler->display->display_options['fields']['professional_affiliation_and_sid_128']['field'] = $side_activities;
$handler->display->display_options['fields']['professional_affiliation_and_sid_128']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['professional_affiliation_and_sid_128']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
$handler->display->display_options['fields']['nothing_2']['table'] = 'views';
$handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_2']['label'] = '';
$handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'You have agreed with the Code of Conduct';
$handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Edit my CV';
$handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'expert/my-cv-edit';
$handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'expert/my-cv';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'CV';
$handler->display->display_options['menu']['name'] = 'menu-my-profile';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['expert_info_for_customer'] = array(
  t('Master'),
  t('Expert'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('.'),
  t('Languages'),
  t('Education'),
  t('Work history'),
  t('All'),
  t('Page'),
);
