<?php

require_once('civicrm.inc');

function pum_expert_mycv_workhistory_form(&$form_state, $name) {
  civicrm_initialize();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  $contact = pum_expert_mycv_get_civi_contact();
  $workhistory = pum_expert_mycv_get_civi_workhistory($contact['id']);

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

  $form['workhistory_entries'] = array(
    '#type' => 'markup',
    '#marpup' => '',
    '#prefix' => '<div id="entry-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['num_workhistory'])) {
    $form_state['num_workhistory'] = count($workhistory) > 0 ? count($workhistory) : 1;
  }
  if (isset($group_info['max_multiple']) && $form_state['num_workhistory'] > $group_info['max_multiple']) {
    $form_state['num_workhistory'] = $group_info['max_multiple'];
    drupal_set_message(t('You cannot have more than @count workhistory items', array('@count' => $group_info['max_multiple'])), 'error');
  }
  $num_workhistory = $form_state['num_workhistory'];

  $addMorePressed = false;
  if (!empty($form_state['add_more_pressed'])) {
    $addMorePressed = true;
  }
  $form_state['add_more_pressed'] = false;

  for ($i = 0; $i < $num_workhistory; $i++) {
    if (!isset($workhistory[$i])) {
      $workhistory[$i] = array();
    }

    $form['workhistory_entries']['workhistory']['workhistory_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Work experience @num', array('@num' => ($i + 1))),
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_name_of_organisation_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Name of organisation'),
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_name_of_organisation_'.$i, 'Workhistory::Name_of_Organisation', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_city_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_city_'.$i, 'Workhistory::City', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_country_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_country_'.$i, 'Workhistory::Country', '', '1152', $addMorePressed),
      '#options' => CRM_Core_PseudoConstant::country(),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_years_from_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('From (year)'),
      '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_years_from_'.$i, 'Workhistory::Yeard_From', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_to_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Until (year)'),
      '#field_suffix' => '<code class="help">Use the full year notation (example: 1980). In case you are still in active employment, write down "ongoing".</code>',
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_to_'.$i, 'Workhistory::To', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_job_title_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Job title'),
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_job_title_'.$i, 'Workhistory::Job_Title', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_description_'.$i] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#field_suffix' => '<code class="help">Specify as accurately as possible the nature of your  tasks, and any special activities.</code>',
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_description_'.$i, 'Workhistory::Description', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_competences_'.$i] = array(
      '#type' => 'textarea',
      '#title' => t('Competences used in this job'),
      '#field_suffix' => '<code class="help">This refers to distinctive expertise, related to the specific responsibilities you had in this position. The purpose of this information is to give the PUM customer insight about specific knowledge that you acquired while you held this job. <br>For instance: commercial insight in the food retail market, specific expertise in the field of ..., product knowledge, product development, financial insight, Human Resources, acquisition etc. (Use terms and areas of expertise that describe your professional duties and used expertise in this specific job).<br><br>It is NOT the intention to mention personal characteristics referring to general qualities regarding creativity, innovation, collaboration, quality minded, team player, leadership etc.</code>',
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_competences_'.$i, 'Workhistory::Competences_used_in_this_job', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_responsibilities_'.$i] = array(
      '#type' => 'textarea',
      '#title' => t('Responsibilities'),
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_responsibilities_'.$i, 'Workhistory::Responsibilities', '', '', $addMorePressed),
      '#required' => true,
    );

    $form['workhistory_entries']['workhistory']['workhistory_'.$i]['workhistory_countries_visited_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Countries visited in relation to the job'),
      '#multiple' => true,
      '#default_value' => pum_expert_mycv_value($values, $workhistory[$i], 'workhistory_countries_visited_'.$i, 'Workhistory::Countries_visited_in_relation_to_the_job', '', '1152', $addMorePressed),
      '#options' => CRM_Core_PseudoConstant::country(),
      '#required' => true,
    );
  }

  $form['workhistory_entries']['buttons']['#type'] = 'markup';
  $form['workhistory_entries']['buttons']['#prefix'] = '<div class="add-more-remove-one-buttons">';
  $form['workhistory_entries']['buttons']['#suffix'] = '</div>';

  if ($form_state['num_workhistory'] > 1) {
    $form['workhistory_entries']['buttons']['remove_workhistory'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('pum_expert_mycv_remove_workhistory'),
      '#ajax' => array(
        'callback' => 'pum_expert_mycv_workhistory_callback',
        'wrapper' => 'entry-fieldset-wrapper',
      ),
      '#limit_validation_errors' => array(),
    );
  }

  $form['workhistory_entries']['buttons']['add_workhistory'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#submit' => array('pum_expert_mycv_add_workhistory'),
    '#ajax' => array(
      'callback' => 'pum_expert_mycv_workhistory_callback',
      'wrapper' => 'entry-fieldset-wrapper',
    ),
    '#limit_validation_errors' => array(),
  );

  $form['previous']['#type'] = 'submit';
  $form['previous']['#value'] = t('Previous');
  $form['previous']['#submit'] = array($name.'_previous');
  $form['previous']['#limit_validation_errors'] = array();
  $form['previous']['#validate'] = array();

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Next');
  $form['next']['#submit'] = array($name.'_next');
  $form['next']['#validate'] = array($name.'_validate');

  return array('form' => $form, 'title' => t('Workhistory'));
}

function pum_expert_mycv_add_workhistory($form, &$form_state) {
  if (!isset($form_state['num_workhistory'])) {
    $form_state['num_workhistory'] = 1;
  }

  $form_state['num_workhistory']++;
  $form_state['add_more_pressed'] = true;
  $form_state['previous'] = false;
  $form_state['next'] = false;
  $form_state['rebuild'] = TRUE;
}

function pum_expert_mycv_remove_workhistory($form, &$form_state) {
  if ($form_state['num_workhistory'] > 1) {
    $form_state['num_workhistory']--;
  }
  $form_state['rebuild'] = TRUE;
  $form_state['previous'] = false;
  $form_state['next'] = false;
}

function pum_expert_mycv_workhistory_callback($form, $form_state) {
  return $form['form']['workhistory_entries'];
}

function pum_expert_mycv_get_civi_workhistory($contact_id) {
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
    $i = 0;
    $field_name = $fields[$value['id']]['custom_group_name'].'::'.$fields[$value['id']]['name'];
    foreach($value as $key => $v) {
      if (is_numeric($key)) {
        $return[$i]['id'] = $key;
        $return[$i][$field_name] = $v;
        $i++;
      }
    }
  }

  return $return;
}

function pum_expert_mycv_civi_save_workhistory($contact_id, $data, $num_workhistory) {
  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  $columns = array();
  foreach($custom_fields['values'] as $field) {
    $fields[$field['name']] = 'custom_'.$field['id'];
    $columns[$field['name']] = $field['column_name'];
  }

  $workhistory = pum_expert_mycv_get_civi_workhistory($contact_id);
  $workhistory_params = array();
  $workhistory_to_remove = array();
  if ($num_workhistory < count($workhistory)) {
    for($i=count($workhistory); $i > $num_workhistory; $i--) {
      $workhistory_to_remove[] = $workhistory[$i-1]['id'];
    }
  }

  $newId = -1;
  for($i=0; $i < $num_workhistory; $i++) {
    if (isset($workhistory[$i])) {
      $key = $workhistory[$i]['id'];
    } else {
      $key = $newId;
      $newId --;
    }

    $workhistory_params[$fields['Name_of_Organisation'].':'.$key] = $data['workhistory_name_of_organisation_'.$i];
    $workhistory_params[$fields['City'].':'.$key] = $data['workhistory_city_'.$i];
    $workhistory_params[$fields['Country'].':'.$key] = $data['workhistory_country_'.$i];
    $workhistory_params[$fields['Yeard_From'].':'.$key] = $data['workhistory_years_from_'.$i];
    $workhistory_params[$fields['To'].':'.$key] = $data['workhistory_to_'.$i];
    $workhistory_params[$fields['Job_Title'].':'.$key] = $data['workhistory_job_title_'.$i];
    $workhistory_params[$fields['Description'].':'.$key] = $data['workhistory_description_'.$i];
    $workhistory_params[$fields['Competences_used_in_this_job'].':'.$key] = $data['workhistory_competences_'.$i];
    $workhistory_params[$fields['Responsibilities'].':'.$key] = $data['workhistory_responsibilities_'.$i];
    $workhistory_params[$fields['Countries_visited_in_relation_to_the_job'].':'.$key] = reset($data['workhistory_countries_visited_'.$i]); //only save first first one
  }

  if (count($workhistory_params)) {
    $workhistory_params['entity_id'] = $contact_id;
    civicrm_api3('CustomValue', 'create', $workhistory_params);
  }

  if (count($workhistory_to_remove) > 0) {
    CRM_Core_DAO::executeQuery("DELETE FROM `".$group_info['table_name']."` WHERE `id` IN (".implode(",", $workhistory_to_remove).")");
  }

  //save work experiences, the api doesnt save multiple values
  $dao = CRM_Core_DAO::executeQuery("SELECT * FROM `".$group_info['table_name']."` WHERE `entity_id` = %1", array(1=>array($contact_id, 'Integer')));
  $i = 0;
  while($dao->fetch()) {
    $sql = "UPDATE `".$group_info['table_name']."` SET `".$columns['Countries_visited_in_relation_to_the_job']."` = %2 WHERE `id` = %1";
    if (isset($data['workhistory_countries_visited_'.$i])) {
      $val = implode(CRM_Core_DAO::VALUE_SEPARATOR, $data['workhistory_countries_visited_'.$i]);
      if (strlen($val)) {
        $val = CRM_Core_DAO::VALUE_SEPARATOR.$val.CRM_Core_DAO::VALUE_SEPARATOR;
        $params = array();
        $params[1] = array($dao->id, 'Integer');
        $params[2] = array($val, 'String');
        CRM_Core_DAO::executeQuery($sql, $params);
      }
    }
    $i++;
  }
}

