<?php

function expert_cv_education_remove($contact_id, $id) {
  global $user;
  civicrm_initialize();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
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
 * Build the form to store the education fields.
 *
 * @param $form
 * @param $form_state
 * @param $contact_id
 * @param null $id
 * @return mixed
 */
function expert_cv_education($form, &$form_state, $contact_id, $id=null) {
  civicrm_initialize();

  $form_state['civicrm']['id'] = $id;
  $form_state['civicrm']['contact_id'] = $contact_id;

  if (!empty($id)) {
    $education = _expert_mycv_education_get($contact_id, $id);
  } else {
    $education = array();
  }
  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form['education_info']['#type'] = 'fieldset';
  $form['education_info']['#title'] = t('Education');
  $form['education_info']['#description'] = 'Please provide us with your relevant education and training details, starting with oldest relevant education and finishing with the most recent. For each additional education or training entry you wish to submit, click the box at the bottom of the form. The maximum number of education entries you can list is 10.';
  $form['education_info']['info'] = array(
    '#type' => 'markup',
    '#markup' => t('Please provide us with your relevant education and training details. Start with your education after completion of secondary school. For each additional education or training you wish to submit, click the box at the bottom of the form.'),
  );

  $form['education_entries']['education']['education_institution_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of Institution'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_institution_name', 'Name_of_Institution', '', '', false),
    '#required' => true,
  );

  $form['education_entries']['education']['education_field_of_study'] = array(
    '#type' => 'textfield',
    '#title' => t('Field of study/major'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_field_of_study', 'Field_of_study_major', '', '', false),
    '#required' => true,
  );

  $form['education_entries']['education']['education_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_city', 'City', '', '', false),
    '#required' => true,
  );

  $form['education_entries']['education']['education_country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_country', 'Country', '', '1152', false),
    '#options' => CRM_Core_PseudoConstant::country(),
    '#required' => true,
  );

  $form['education_entries']['education']['education_education_level'] = array(
    '#type' => 'select',
    '#title' => t('Education level'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_education_level', 'Education_level', '', '', false),
    '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('education_level_20140825212618'),
    '#required' => true,
  );

  $form['education_entries']['education']['education_years_from'] = array(
    '#type' => 'textfield',
    '#title' => t('Years from'),
    '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_years_from', 'Years_From', '', '', false),
    '#rules' => array(
      'numeric',
      'length[4]',
    ),
    '#required' => true,
  );

  $form['education_entries']['education']['education_to'] = array(
    '#type' => 'textfield',
    '#title' => t('Years to'),
    '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_to', 'To', '', '', false),
    '#rules' => array(
      'numeric',
      'length[4]',
    ),
    '#required' => true,
  );

  $form['education_entries']['education']['education_diploma_degree'] = array(
    '#type' => 'select',
    '#title' => t('Diploma/Degree'),
    '#default_value' => pum_expert_mycv_value($values, $education, 'education_diploma_degree', 'Diploma_Degree', '', '', false),
    '#options' => array('' => t('- None -'), '1' => t('Yes'), '0' => t('No')),
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
 * Save the education into CiviCRM.
 *
 * @param $form
 * @param $form_state
 */
function expert_cv_education_submit($form, &$form_state) {
  global $user;

  $id = $form_state['civicrm']['id'];
  $contact_id = $form_state['civicrm']['contact_id'];

  civicrm_initialize();

  //update education
  _expert_mycv_education_save($contact_id, $id, $form_state['values']);

  drupal_set_message(t('Your CV is successfully updated'));
  if (in_array("Expert", $user->roles)) {
    $form_state['redirect'] = 'expert/my-cv';
  } elseif (in_array("Candidate expert", $user->roles)) {
    $form_state['redirect'] = 'portal';
  }
}

/**
 * Switches two education records
 * 
 * @param $contact_id
 *   The contact ID.
 * @param $id_1
 *   The ID of record 1.
 * @param $id_2
 *   The ID of record 2.
 */
function expert_cv_education_switch($contact_id, $id_1, $id_2) {
  global $user;
  civicrm_initialize();
  $record_1 = _expert_cv_education_get($contact_id, $id_1);
  $record_2 = _expert_cv_education_get($contact_id, $id_2);
  _expert_mycv_education_save($contact_id, $id_2, $record_1);
  _expert_mycv_education_save($contact_id, $id_1, $record_2);
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
function _expert_cv_education_get($contact_id, $id) {
  $education = _expert_mycv_education_get($contact_id, $id);
  $values = array();
  $record = array();
  $record['education_institution_name'] = pum_expert_mycv_value($values, $education, 'education_institution_name', 'Name_of_Institution', '', '', false);
  $record['education_field_of_study'] = pum_expert_mycv_value($values, $education, 'education_field_of_study', 'Field_of_study_major', '', '', false);
  $record['education_city'] = pum_expert_mycv_value($values, $education, 'education_city', 'City', '', '', false);
  $record['education_country'] = pum_expert_mycv_value($values, $education, 'education_country', 'Country', '', '', false);
  $record['education_education_level'] = pum_expert_mycv_value($values, $education, 'education_education_level', 'Education_level', '', '', false);
  $record['education_years_from'] = pum_expert_mycv_value($values, $education, 'education_years_from', 'Years_From', '', '', false);
  $record['education_to'] = pum_expert_mycv_value($values, $education, 'education_to', 'To', '', '', false);
  $record['education_diploma_degree'] = pum_expert_mycv_value($values, $education, 'education_diploma_degree', 'Diploma_Degree', '', '', false);
  if (is_array($record['education_education_level'])) {
    $record['education_education_level'] = reset($record['education_education_level']);
  }
  return $record;
}

/**
 * Save education into CiviCRM
 *
 * @param $contact_id
 * @param $id
 * @param $data
 * @throws \CiviCRM_API3_Exception
 */
function _expert_mycv_education_save($contact_id, $id, $data) {
  if (!empty($id)) {
    $key = $id;
  } else {
    $key = -1;
  }

  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  foreach($custom_fields['values'] as $field) {
    $fields[$field['name']] = 'custom_'.$field['id'];
  }

  $education_params[$fields['Name_of_Institution'].':'.$key] = $data['education_institution_name'];
  $education_params[$fields['Field_of_study_major'].':'.$key] = $data['education_field_of_study'];
  $education_params[$fields['City'].':'.$key] = $data['education_city'];
  $education_params[$fields['Country'].':'.$key] = $data['education_country'];
  $education_params[$fields['Education_level'].':'.$key] = array($data['education_education_level']);
  $education_params[$fields['Years_From'].':'.$key] = $data['education_years_from'];
  $education_params[$fields['To'].':'.$key] = $data['education_to'];
  $education_params[$fields['Diploma_Degree'].':'.$key] = $data['education_diploma_degree'];

  if (count($education_params)) {
    $education_params['entity_id'] = $contact_id;
    civicrm_api3('CustomValue', 'create', $education_params);
  }
}

/**
 * Returns the education data for a civicrm contact_id and a record id.
 *
 * @param $contact_id
 * @param $id
 * @return array
 * @throws \CiviCRM_API3_Exception
 */
function _expert_mycv_education_get($contact_id, $id) {
  $params = array();
  $params['entity_id'] = $contact_id;

  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
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
    $field_name = $fields[$value['id']]['name'];
    foreach($value as $key => $v) {
      if (is_numeric($key) && $id == $key) {
        $return['id'] = $key;
        $return[$field_name] = $v;
      }
    }
  }

  return $return;
}