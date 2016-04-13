<?php

/**
 * Remove a workhistory item
 *
 * @param $contact_id
 * @param $id
 * @throws \CiviCRM_API3_Exception
 */
function expert_cv_workhistory_remove($contact_id, $id) {
  global $user;
  civicrm_initialize();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  CRM_Core_DAO::executeQuery("DELETE FROM `".$group_info['table_name']."` WHERE `id` = %1 AND `entity_id` = %2", array(
    1 => array($id, 'Integer'),
    2 => array($contact_id, 'Integer')
  ));
  drupal_set_message(t('Your CV is successfully updated'));
  if (in_array("Expert", $user->roles)) {
    drupal_goto('expert/my-cv');
  } elseif (in_array("Candidate expert", $user->roles)) {
    drupal_goto('portal');
  }
}

/**
 * Implements hook_form().
 *
 * Build the form to store the workhistory fields.
 *
 * @param $form
 * @param $form_state
 * @param $contact_id
 * @param null $id
 * @return mixed
 */
function expert_cv_workhistory($form, &$form_state, $contact_id, $id=null) {
  civicrm_initialize();

  $form_state['civicrm']['id'] = $id;
  $form_state['civicrm']['contact_id'] = $contact_id;

  if (!empty($id)) {
    $workhistory = _expert_mycv_workhistory_get($contact_id, $id);
  } else {
    $workhistory = array();
  }
  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form['workhistory_info']['#type'] = 'fieldset';
  $form['workhistory_info']['#title'] = t('Workhistory');
  $form['workhistory_info']['#description'] = 'Please provide us with your relevant work experience details starting with your most recent work experience and working backwards in chronological order. For each additional work experience entry you wish to submit, click the box at the bottom of the form. The maximum number of work experience entries you can list is 10.';
  $form['workhistory_info']['info'] = array(
    '#type' => 'markup',
    '#markup' => t('Please provide us with your relevant work experience details. For each additional work experience you wish to submit, klick the box at the bottom of the form.'),
  );

  $form['workhistory_entries']['workhistory_name_of_organisation'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of organisation'),
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_name_of_organisation', 'Workhistory::Name_of_Organisation', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_city', 'Workhistory::City', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_country', 'Workhistory::Country', '', '1152', false),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_years_from'] = array(
    '#type' => 'textfield',
    '#title' => t('From (year)'),
    '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_years_from', 'Workhistory::Yeard_From', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_to'] = array(
    '#type' => 'textfield',
    '#title' => t('Until (year)'),
    '#field_suffix' => '<code class="help">Use the full year notation (example: 1980). In case you are still in active employment, write down "ongoing".</code>',
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_to', 'Workhistory::To', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_job_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Job title'),
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_job_title', 'Workhistory::Job_Title', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#field_suffix' => '<code class="help">Specify as accurately as possible the nature of your  tasks, and any special activities.</code>',
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_description', 'Workhistory::Description', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_competences'] = array(
    '#type' => 'textarea',
    '#title' => t('Competences used in this job'),
    '#field_suffix' => '<code class="help">This refers to distinctive expertise, related to the specific responsibilities you had in this position. The purpose of this information is to give the PUM customer insight about specific knowledge that you acquired while you held this job. <br>For instance: commercial insight in the food retail market, specific expertise in the field of ..., product knowledge, product development, financial insight, Human Resources, acquisition etc. (Use terms and areas of expertise that describe your professional duties and used expertise in this specific job).<br><br>It is NOT the intention to mention personal characteristics referring to general qualities regarding creativity, innovation, collaboration, quality minded, team player, leadership etc.</code>',
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_competences', 'Workhistory::Competences_used_in_this_job', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_responsibilities'] = array(
    '#type' => 'textarea',
    '#title' => t('Responsibilities'),
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_responsibilities', 'Workhistory::Responsibilities', '', '', false),
    '#required' => true,
  );

  $form['workhistory_entries']['workhistory_countries_visited'] = array(
    '#type' => 'select',
    '#title' => t('Countries visited in relation to the job'),
    '#multiple' => true,
    '#default_value' => pum_expert_mycv_value($values, $workhistory, 'workhistory_countries_visited', 'Workhistory::Countries_visited_in_relation_to_the_job', '', '1152', false),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#required' => true,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['actions']['cancel'] = array(
    '#type'   => 'submit',
    '#value'  => t('Cancel'),
    '#submit' => array('pum_expert_cv_cancel'),
    '#limit_validation_errors' => array(),
  );

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');

  return $form;
}
/**
 * Implements hook_submit().
 *
 * Save the workhistory into CiviCRM.
 *
 * @param $form
 * @param $form_state
 */
function expert_cv_workhistory_submit($form, &$form_state) {
  global $user;

  $id = $form_state['civicrm']['id'];
  $contact_id = $form_state['civicrm']['contact_id'];

  civicrm_initialize();

  //update education
  _expert_mycv_workhistory_save($contact_id, $id, $form_state['values']);

  drupal_set_message(t('Your CV is successfully updated'));
  if (in_array("Expert", $user->roles)) {
    $form_state['redirect'] = 'expert/my-cv';
  } elseif (in_array("Candidate expert", $user->roles)) {
    $form_state['redirect'] = 'portal';
  }
}

/**
 * Switches two workhistory records
 *
 * @param $contact_id
 *   The contact ID.
 * @param $id_1
 *   The ID of record 1.
 * @param $id_2
 *   The ID of record 2.
 */
function expert_cv_workhistory_switch($contact_id, $id_1, $id_2) {
  global $user;
  civicrm_initialize();
  $record_1 = _expert_cv_workhistory_get($contact_id, $id_1);
  $record_2 = _expert_cv_workhistory_get($contact_id, $id_2);
  _expert_mycv_workhistory_save($contact_id, $id_2, $record_1);
  _expert_mycv_workhistory_save($contact_id, $id_1, $record_2);
  drupal_set_message(t('Your CV is successfully updated'));
  if (in_array("Expert", $user->roles)) {
    drupal_goto('expert/my-cv');
  } elseif (in_array("Candidate expert", $user->roles)) {
    drupal_goto('portal');
  }
}

/**
 * Get the record
 *
 * @param $contact_id
 *   The contact ID.
 * @param $id
 *   The record ID.
 *
 * @return array
 *   The record.
 */
function _expert_cv_workhistory_get($contact_id, $id) {
  $workhistory = _expert_mycv_workhistory_get($contact_id, $id);
  $values = array();
  $record = array();
  $record['workhistory_name_of_organisation'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_name_of_organisation', 'Workhistory::Name_of_Organisation', '', '', false);
  $record['workhistory_city'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_city', 'Workhistory::City', '', '', false);
  $record['workhistory_country'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_country', 'Workhistory::Country', '', '', false);
  $record['workhistory_years_from'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_years_from', 'Workhistory::Yeard_From', '', '', false);
  $record['workhistory_to'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_to', 'Workhistory::To', '', '', false);
  $record['workhistory_job_title'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_job_title', 'Workhistory::Job_Title', '', '', false);
  $record['workhistory_description'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_description', 'Workhistory::Description', '', '', false);
  $record['workhistory_competences'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_competences', 'Workhistory::Competences_used_in_this_job', '', '', false);
  $record['workhistory_responsibilities'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_responsibilities', 'Workhistory::Responsibilities', '', '', false);
  $record['workhistory_countries_visited'] = pum_expert_mycv_value($values, $workhistory, 'workhistory_countries_visited', 'Workhistory::Countries_visited_in_relation_to_the_job', '', '', false);

  return $record;
}

/**
 * Save workhistory into CiviCRM
 *
 * @param $contact_id
 * @param $id
 * @param $data
 * @throws \CiviCRM_API3_Exception
 */
function _expert_mycv_workhistory_save($contact_id, $id, $data) {
  if (!empty($id)) {
    $key = $id;
  }
  else {
    $key = -1;
  }

  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  $columns = array();
  foreach($custom_fields['values'] as $field) {
    $fields[$field['name']] = 'custom_'.$field['id'];
    $columns[$field['name']] = $field['column_name'];
  }

  $workhistory_params[$fields['Name_of_Organisation'].':'.$key] = $data['workhistory_name_of_organisation'];
  $workhistory_params[$fields['City'].':'.$key] = $data['workhistory_city'];
  $workhistory_params[$fields['Country'].':'.$key] = $data['workhistory_country'];
  $workhistory_params[$fields['Yeard_From'].':'.$key] = $data['workhistory_years_from'];
  $workhistory_params[$fields['To'].':'.$key] = $data['workhistory_to'];
  $workhistory_params[$fields['Job_Title'].':'.$key] = $data['workhistory_job_title'];
  $workhistory_params[$fields['Description'].':'.$key] = $data['workhistory_description'];
  $workhistory_params[$fields['Competences_used_in_this_job'].':'.$key] = $data['workhistory_competences'];
  $workhistory_params[$fields['Responsibilities'].':'.$key] = $data['workhistory_responsibilities'];
  $workhistory_params[$fields['Countries_visited_in_relation_to_the_job'].':'.$key] = reset($data['workhistory_countries_visited']); //only save first first one

  if (count($workhistory_params)) {
    $workhistory_params['entity_id'] = $contact_id;
    $return = civicrm_api3('CustomValue', 'create', $workhistory_params);
  }


  //save work experiences, the api doesnt save multiple values
  if ($id) {
    $dao = CRM_Core_DAO::executeQuery("SELECT * FROM `".$group_info['table_name']."` WHERE `entity_id` = %1 and id = %2 LIMIT 0,1", array(
      1=>array($contact_id, 'Integer'),
      2=>array($id, 'Integer')
    ));
  } else {
    $dao = CRM_Core_DAO::executeQuery("SELECT * FROM `".$group_info['table_name']."` WHERE `entity_id` = %1 ORDER BY id DESC LIMIT 0,1", array(
      1=>array($contact_id, 'Integer')
    ));
  }
  while($dao->fetch()) {
    $sql = "UPDATE `".$group_info['table_name']."` SET `".$columns['Countries_visited_in_relation_to_the_job']."` = %2 WHERE `id` = %1";
    if (isset($data['workhistory_countries_visited']) && is_array($data['workhistory_countries_visited'])) {
      $val = implode(CRM_Core_DAO::VALUE_SEPARATOR, $data['workhistory_countries_visited']);
      if (strlen($val)) {
        $val = CRM_Core_DAO::VALUE_SEPARATOR.$val.CRM_Core_DAO::VALUE_SEPARATOR;
        $params = array();
        $params[1] = array($dao->id, 'Integer');
        $params[2] = array($val, 'String');
        CRM_Core_DAO::executeQuery($sql, $params);
      }
    }
  }
}

/**
 * Returns the workhistory data for a civicrm contact_id and a record id.
 *
 * @param $contact_id
 * @param $id
 * @return array
 * @throws \CiviCRM_API3_Exception
 */
function _expert_mycv_workhistory_get($contact_id, $id) {
  $params = array();
  $params['entity_id'] = $contact_id;

  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  foreach($custom_fields['values'] as $field) {
    $fields[$field['id']] = array(
      'name' => $field['name'],
      'id' => $field['id'],
      'custom_group_id' => $field['custom_group_id'],
      'custom_group_name' => $group_info['name'],
    );
    $params['return.custom_'.$field['id']] = 1;
  }

  $values = civicrm_api3('CustomValue', 'get', $params);
  $return = array();
  foreach($values['values'] as $value) {
    $field_name = $fields[$value['id']]['custom_group_name'].'::'.$fields[$value['id']]['name'];
    foreach($value as $key => $v) {
      if (is_numeric($key) && $key == $id) {
        $return['id'] = $key;
        $return[$field_name] = $v;
      }
    }
  }

  return $return;
}