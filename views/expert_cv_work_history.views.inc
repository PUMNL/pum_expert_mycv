<?php

$cgroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
$name = civicrm_api3('CustomField', 'getvalue', array('name' => 'Name_of_Organisation', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$title = civicrm_api3('CustomField', 'getvalue', array('name' => 'Job_Title', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$city = civicrm_api3('CustomField', 'getvalue', array('name' => 'City', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$country = civicrm_api3('CustomField', 'getvalue', array('name' => 'Country', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$responsebilities = civicrm_api3('CustomField', 'getvalue', array('name' => 'Responsibilities', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$description = civicrm_api3('CustomField', 'getvalue', array('name' => 'Description', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$competences = civicrm_api3('CustomField', 'getvalue', array('name' => 'Competences_used_in_this_job', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$from = civicrm_api3('CustomField', 'getvalue', array('name' => 'Yeard_From', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$to = civicrm_api3('CustomField', 'getvalue', array('name' => 'To', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$countries_visited = civicrm_api3('CustomField', 'getvalue', array('name' => 'Countries_visited_in_relation_to_the_job', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));

$view = new view();
$view->name = 'expert_cv_work_experience_';
$view->description = 'Work history of expert CV';
$view->tag = 'expert cv';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Expert CV (Work experience)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<div class="pumnet purple"><a href="/expert/cv-edit-workhistory/!1/add" class="pumnet button purple">Add workhistory</a></div>';
$handler->display->display_options['header']['area']['format'] = 'filtered_html';
$handler->display->display_options['header']['area']['tokenize'] = TRUE;
/* Field: CiviCRM Custom: Workhistory: ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Custom: Workhistory: Name of Organisation */
$handler->display->display_options['fields']['name_of_organisation_622']['id'] = 'name_of_organisation_622';
$handler->display->display_options['fields']['name_of_organisation_622']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['name_of_organisation_622']['field'] = $name;
$handler->display->display_options['fields']['name_of_organisation_622']['label'] = '';
$handler->display->display_options['fields']['name_of_organisation_622']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['name_of_organisation_622']['element_type'] = 'strong';
$handler->display->display_options['fields']['name_of_organisation_622']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Workhistory: Job Title */
$handler->display->display_options['fields']['job_title_627']['id'] = 'job_title_627';
$handler->display->display_options['fields']['job_title_627']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['job_title_627']['field'] = $title;
$handler->display->display_options['fields']['job_title_627']['label'] = '';
$handler->display->display_options['fields']['job_title_627']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['job_title_627']['element_type'] = 'em';
$handler->display->display_options['fields']['job_title_627']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Workhistory: City */
$handler->display->display_options['fields']['city_623']['id'] = 'city_623';
$handler->display->display_options['fields']['city_623']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['city_623']['field'] = $city;
$handler->display->display_options['fields']['city_623']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Workhistory: Country */
$handler->display->display_options['fields']['country_624']['id'] = 'country_624';
$handler->display->display_options['fields']['country_624']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['country_624']['field'] = $country;
/* Field: CiviCRM Custom: Workhistory: Responsibilities */
$handler->display->display_options['fields']['responsibilities_634']['id'] = 'responsibilities_634';
$handler->display->display_options['fields']['responsibilities_634']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['responsibilities_634']['field'] = $responsebilities;
/* Field: CiviCRM Custom: Workhistory: Description */
$handler->display->display_options['fields']['description_632']['id'] = 'description_632';
$handler->display->display_options['fields']['description_632']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['description_632']['field'] = $description;
/* Field: CiviCRM Custom: Workhistory: Competences used in this job */
$handler->display->display_options['fields']['competences_used_in_this_job_633']['id'] = 'competences_used_in_this_job_633';
$handler->display->display_options['fields']['competences_used_in_this_job_633']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['competences_used_in_this_job_633']['field'] = $competences;
/* Field: CiviCRM Custom: Workhistory: Countries visited in relation to the job */
$handler->display->display_options['fields']['countries_visited_in_relation_to_635']['id'] = 'countries_visited_in_relation_to_635';
$handler->display->display_options['fields']['countries_visited_in_relation_to_635']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['countries_visited_in_relation_to_635']['field'] = $countries_visited;
/* Field: CiviCRM Custom: Workhistory: Years - From */
$handler->display->display_options['fields']['yeard_from_625']['id'] = 'yeard_from_625';
$handler->display->display_options['fields']['yeard_from_625']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['yeard_from_625']['field'] = $from;
$handler->display->display_options['fields']['yeard_from_625']['label'] = '';
$handler->display->display_options['fields']['yeard_from_625']['exclude'] = TRUE;
$handler->display->display_options['fields']['yeard_from_625']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['yeard_from_625']['element_type'] = '0';
$handler->display->display_options['fields']['yeard_from_625']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Workhistory: To */
$handler->display->display_options['fields']['to_626']['id'] = 'to_626';
$handler->display->display_options['fields']['to_626']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['to_626']['field'] = $to;
$handler->display->display_options['fields']['to_626']['label'] = '';
$handler->display->display_options['fields']['to_626']['exclude'] = TRUE;
$handler->display->display_options['fields']['to_626']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['to_626']['element_type'] = '0';
$handler->display->display_options['fields']['to_626']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Period';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[yeard_from_625] - [to_626]';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_1']['id'] = 'php_1';
$handler->display->display_options['fields']['php_1']['table'] = 'views';
$handler->display->display_options['fields']['php_1']['field'] = 'php';
$handler->display->display_options['fields']['php_1']['label'] = '';
$handler->display->display_options['fields']['php_1']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['text'] = 'Move up';
$handler->display->display_options['fields']['php_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['path'] = 'expert/cv-edit-workhistory/[id_1]/[id]/switch/[php_1]';
$handler->display->display_options['fields']['php_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_1']['php_value'] = 'return _pum_expert_mycv_get_previous_record_id($row->id_1, $row->id, "'.$cgroup['table_name'].'");';
$handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = '';
$handler->display->display_options['fields']['php']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['text'] = 'Move down';
$handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['path'] = 'expert/cv-edit-workhistory/[id_1]/[id]/switch/[php]';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = 'return _pum_expert_mycv_get_next_record_id($row->id_1, $row->id, "'.$cgroup['table_name'].'");';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Edit';
$handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'expert/cv-edit-workhistory/[id_1]/[id]';
$handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
$handler->display->display_options['fields']['nothing_2']['table'] = 'views';
$handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_2']['label'] = '';
$handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'Remove';
$handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_2']['alter']['path'] = 'expert/cv-edit-workhistory/[id_1]/[id]/delete';
$handler->display->display_options['fields']['nothing_2']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
$translatables['expert_cv_work_experience_'] = array(
  t('Master'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« first'),
  t('‹ previous'),
  t('next ›'),
  t('last »'),
  t('City'),
  t('Country'),
  t('Responsibilities'),
  t('Description'),
  t('Competences used in this job'),
  t('Countries visited in relation to the job'),
  t('Period'),
  t('[yeard_from_625] - [to_626]'),
  t('All'),
);
