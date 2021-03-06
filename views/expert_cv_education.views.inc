<?php

$cgroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
$name = civicrm_api3('CustomField', 'getvalue', array('name' => 'Name_of_Institution', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$level = civicrm_api3('CustomField', 'getvalue', array('name' => 'Education_level', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$major = civicrm_api3('CustomField', 'getvalue', array('name' => 'Field_of_study_major', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$city = civicrm_api3('CustomField', 'getvalue', array('name' => 'City', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$country = civicrm_api3('CustomField', 'getvalue', array('name' => 'Country', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$diploma = civicrm_api3('CustomField', 'getvalue', array('name' => 'Diploma_Degree', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$from = civicrm_api3('CustomField', 'getvalue', array('name' => 'Years_From', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));
$to = civicrm_api3('CustomField', 'getvalue', array('name' => 'To', 'return' => 'column_name', 'custom_group_id' => $cgroup['id']));

$view = new view();
$view->name = 'expert_cv_education_';
$view->description = 'Education of expert cv';
$view->tag = 'expert cv';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Expert CV (Education)';
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
/* Header: Global: PHP */
$handler->display->display_options['header']['php']['id'] = 'php';
$handler->display->display_options['header']['php']['table'] = 'views';
$handler->display->display_options['header']['php']['field'] = 'php';
$handler->display->display_options['header']['php']['empty'] = TRUE;
$handler->display->display_options['header']['php']['php_output'] = '<?php
$expert_id = reset($view->args);
if (_pum_expert_cv_is_viewing_own_cv($view)) {
echo \'<div class="pumnet purple"><a href="/expert/cv-edit-education/\'.$expert_id.\'/add" class="pumnet button purple">Add an education</a></div>\';
} ?>';
/* Field: CiviCRM Custom: Education: ID */
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
/* Field: CiviCRM Custom: Education: Name of Institution */
$handler->display->display_options['fields']['name_of_institution_586']['id'] = 'name_of_institution_586';
$handler->display->display_options['fields']['name_of_institution_586']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['name_of_institution_586']['field'] = $name;
$handler->display->display_options['fields']['name_of_institution_586']['label'] = '';
$handler->display->display_options['fields']['name_of_institution_586']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['name_of_institution_586']['element_type'] = 'strong';
$handler->display->display_options['fields']['name_of_institution_586']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Education: Education level */
$handler->display->display_options['fields']['education_level_590']['id'] = 'education_level_590';
$handler->display->display_options['fields']['education_level_590']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['education_level_590']['field'] = $level;
$handler->display->display_options['fields']['education_level_590']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Education: Field of study/major */
$handler->display->display_options['fields']['field_of_study_major_587']['id'] = 'field_of_study_major_587';
$handler->display->display_options['fields']['field_of_study_major_587']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['field_of_study_major_587']['field'] = $major;
$handler->display->display_options['fields']['field_of_study_major_587']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Education: City */
$handler->display->display_options['fields']['city_588']['id'] = 'city_588';
$handler->display->display_options['fields']['city_588']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['city_588']['field'] = $city;
$handler->display->display_options['fields']['city_588']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Education: Country */
$handler->display->display_options['fields']['country_589']['id'] = 'country_589';
$handler->display->display_options['fields']['country_589']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['country_589']['field'] = $country;
/* Field: CiviCRM Custom: Education: Diploma/Degree */
$handler->display->display_options['fields']['diploma_degree_593']['id'] = 'diploma_degree_593';
$handler->display->display_options['fields']['diploma_degree_593']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['diploma_degree_593']['field'] = $diploma;
/* Field: CiviCRM Custom: Education: Years - From */
$handler->display->display_options['fields']['years_from_591']['id'] = 'years_from_591';
$handler->display->display_options['fields']['years_from_591']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['years_from_591']['field'] = $from;
$handler->display->display_options['fields']['years_from_591']['label'] = '';
$handler->display->display_options['fields']['years_from_591']['exclude'] = TRUE;
$handler->display->display_options['fields']['years_from_591']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['years_from_591']['element_label_colon'] = FALSE;
/* Field: CiviCRM Custom: Education: To */
$handler->display->display_options['fields']['to_592']['id'] = 'to_592';
$handler->display->display_options['fields']['to_592']['table'] = $cgroup['table_name'];
$handler->display->display_options['fields']['to_592']['field'] = $to;
$handler->display->display_options['fields']['to_592']['label'] = '';
$handler->display->display_options['fields']['to_592']['exclude'] = TRUE;
$handler->display->display_options['fields']['to_592']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['to_592']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Period';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[years_from_591] - [to_592]';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_1']['id'] = 'php_1';
$handler->display->display_options['fields']['php_1']['table'] = 'views';
$handler->display->display_options['fields']['php_1']['field'] = 'php';
$handler->display->display_options['fields']['php_1']['label'] = '';
$handler->display->display_options['fields']['php_1']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['text'] = 'Move up';
$handler->display->display_options['fields']['php_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['path'] = 'expert/cv-edit-education/[id_1]/[id]/switch/[php_1]';
$handler->display->display_options['fields']['php_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_1']['php_value'] = 'if (_pum_expert_cv_is_viewing_own_cv($view)) {
return _pum_expert_mycv_get_previous_record_id($row->id_1, $row->id, "'.$cgroup['table_name'].'");
}
return \'\';';
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
$handler->display->display_options['fields']['php']['alter']['path'] = 'expert/cv-edit-education/[id_1]/[id]/switch/[php]';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = 'if (_pum_expert_cv_is_viewing_own_cv($view)) {
return _pum_expert_mycv_get_next_record_id($row->id_1, $row->id, "'.$cgroup['table_name'].'");
}
return \'\';';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'php';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Edit';
$handler->display->display_options['fields']['nothing_1']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'expert/cv-edit-education/[id_1]/[id]';
$handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['use_php_setup'] = 0;
$handler->display->display_options['fields']['nothing_1']['php_value'] = 'if (_pum_expert_cv_is_viewing_own_cv($view)) {
return \'Edit\';
}
return \'\';';
$handler->display->display_options['fields']['nothing_1']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['nothing_1']['php_click_sortable'] = '';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
$handler->display->display_options['fields']['nothing_2']['table'] = 'views';
$handler->display->display_options['fields']['nothing_2']['field'] = 'php';
$handler->display->display_options['fields']['nothing_2']['label'] = '';
$handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'Remove';
$handler->display->display_options['fields']['nothing_2']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing_2']['alter']['path'] = 'expert/cv-edit-education/[id_1]/[id]/delete';
$handler->display->display_options['fields']['nothing_2']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_2']['use_php_setup'] = 0;
$handler->display->display_options['fields']['nothing_2']['php_value'] = 'if (_pum_expert_cv_is_viewing_own_cv($view)) {
return \'Remove\';
}
return \'\';';
$handler->display->display_options['fields']['nothing_2']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['nothing_2']['php_click_sortable'] = '';
/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
$translatables['expert_cv_education_'] = array(
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
  t('Education level'),
  t('Field of study/major'),
  t('City'),
  t('Country'),
  t('Diploma/Degree'),
  t('Period'),
  t('[years_from_591] - [to_592]'),
  t('All'),
);
