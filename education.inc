<?php

require_once('civicrm.inc');

function pum_expert_mycv_education_form(&$form_state, $rebuild=false) {
  $contact = pum_expert_mycv_get_civi_contact();
  $educations = pum_expert_mycv_get_civi_education($contact['id']);

  $form['education_info']['#type'] = 'fieldset';
  $form['education_info']['#title'] = t('Education');
  $form['education_info']['#description'] = 'Please provide us with your relevant education and training details, starting with oldest relevant education and finishing with the most recent. For each additional education or training entry you wish to submit, click the box at the bottom of the form. The maximum number of education entries you can list is 10.';
  $form['education_info']['info'] = array(
    '#type' => 'markup',
    '#markup' => t('Please provide us with your relevant education and training details. Start with your education after completion of secondary school. For each additional education or training you wish to submit, click the box at the bottom of the form.'),
  );

  $form['education_entries'] = array(
    '#type' => 'markup',
    '#markup' => '',
    '#prefix' => '<div id="entry-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (!empty($form_state['next']) && $rebuild) {
    $form_state['num_educations'] = count($educations) > 0 ? count($educations) : 1;
  }

  if (empty($form_state['num_educations'])) {
    $form_state['num_educations'] = count($educations) > 0 ? count($educations) : 1;
  }

  $addMorePressed = false;
  if (!empty($form_state['add_more_pressed'])) {
    $addMorePressed = true;
  }
  $form_state['add_more_pressed'] = false;

  for ($i = 0; $i < $form_state['num_educations']; $i++) {
    $form['education_entries']['education']['education_'.$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Education @num', array('@num' => ($i+1))),
    );

    $form['education_entries']['education']['education_'.$i]['education_institution_name_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Name of Institution'),
      '#default_value' => isset($educations[$i]['Name_of_Institution']) && !$addMorePressed ? $educations[$i]['Name_of_Institution'] : '',
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_field_of_study_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Field of study/major'),
      '#default_value' => isset($educations[$i]['Field_of_study_major']) && !$addMorePressed ? $educations[$i]['Field_of_study_major'] : '',
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_city_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => isset($educations[$i]['City']) && !$addMorePressed ? $educations[$i]['City'] : '',
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_country_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => !empty($educations[$i]['Country']) && !$addMorePressed ? $educations[$i]['Country'] : '1152',
      '#options' => CRM_Core_PseudoConstant::country(),
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_education_level_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Education level'),
      '#default_value' => isset($educations[$i]['Education_level']) && !$addMorePressed ? $educations[$i]['Education_level'] : '',
      '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('education_level_20140825212618'),
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_years_from_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Years from'),
      '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
      '#default_value' => isset($educations[$i]['Years_From']) && !$addMorePressed ? $educations[$i]['Years_From'] : '',
      '#rules' => array(
        'numeric',
        'length[4]',
      ),
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_to_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Years to'),
      '#field_suffix' => '<code class="help">Use the full year notation (example: 1980)</code>',
      '#default_value' => isset($educations[$i]['To']) && !$addMorePressed ? $educations[$i]['To'] : '',
      '#rules' => array(
        'numeric',
        'length[4]',
      ),
      '#required' => true,
    );

    $form['education_entries']['education']['education_'.$i]['education_diploma_degree_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Diploma/Degree'),
      '#default_value' => isset($educations[$i]['Diploma_Degree']) && !$addMorePressed ? $educations[$i]['Diploma_Degree'] : '',
      '#options' => array('' => t('- None -'), '1' => t('Yes'), '0' => t('No')),
      '#required' => true,
    );
  }

  $form['education_entries']['buttons']['#type'] = 'markup';
  $form['education_entries']['buttons']['#prefix'] = '<div class="add-more-remove-one-buttons">';
  $form['education_entries']['buttons']['#suffix'] = '</div>';

  if ($form_state['num_educations'] > 1) {
    $form['education_entries']['buttons']['remove_education'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('pum_expert_mycv_remove_education'),
      '#ajax' => array(
        'callback' => 'pum_expert_mycv_education_callback',
        'wrapper' => 'entry-fieldset-wrapper',
      ),
      '#limit_validation_errors' => array(),
    );
  }

  $form['education_entries']['buttons']['add_education'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#submit' => array('pum_expert_mycv_add_education'),
    '#ajax' => array(
      'callback' => 'pum_expert_mycv_education_callback',
      'wrapper' => 'entry-fieldset-wrapper',
    ),
    '#limit_validation_errors' => array(),
  );

  return array('form' => $form, 'title' => t('Education'));
}

function pum_expert_mycv_civi_save_education($contact_id, $data, $num_educations) {
  $fields = array();
  $group_info =  civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
  $custom_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $group_info['id']));
  foreach($custom_fields['values'] as $field) {
    $fields[$field['name']] = 'custom_'.$field['id'];
  }

  $educations = pum_expert_mycv_get_civi_education($contact_id);
  $education_params = array();
  $educations_to_remove = array();
  if ($num_educations < count($educations)) {
    for($i=count($educations); $i > $num_educations; $i--) {
      $educations_to_remove[] = $educations[$i-1]['id'];
    }
  }

  $newId = -1;

  for($i=0; $i < $num_educations; $i++) {
    if (isset($educations[$i])) {
      $key = $educations[$i]['id'];
    } else {
      $key = $newId;
      $newId --;
    }

    $education_params[$fields['Name_of_Institution'].':'.$key] = $data['education_institution_name_'.$i];
    $education_params[$fields['Field_of_study_major'].':'.$key] = $data['education_field_of_study_'.$i];
    $education_params[$fields['City'].':'.$key] = $data['education_city_'.$i];
    $education_params[$fields['Country'].':'.$key] = $data['education_country_'.$i];
    $education_params[$fields['Education_level'].':'.$key] = $data['education_education_level_'.$i];
    $education_params[$fields['Years_From'].':'.$key] = $data['education_years_from_'.$i];
    $education_params[$fields['To'].':'.$key] = $data['education_to_'.$i];
    $education_params[$fields['Diploma_Degree'].':'.$key] = $data['education_diploma_degree_'.$i];
  }

  if (count($education_params)) {
    $education_params['entity_id'] = $contact_id;
    civicrm_api3('CustomValue', 'create', $education_params);
  }

  if (count($educations_to_remove) > 0) {
    CRM_Core_DAO::executeQuery("DELETE FROM `".$group_info['table_name']."` WHERE `id` IN (".implode(",", $educations_to_remove).")");
  }
}


function pum_expert_mycv_add_education($form, &$form_state) {
  if (!isset($form_state['num_educations'])) {
    $form_state['num_educations'] = 1;
  }

  $form_state['num_educations']++;
  $form_state['add_more_pressed'] = true;
  $form_state['rebuild'] = TRUE;
  $form_state['step'] = $form_state['step'] -1;
}

function pum_expert_mycv_remove_education($form, &$form_state) {
  if ($form_state['num_educations'] > 1) {
    $form_state['num_educations']--;
  }
  $form_state['rebuild'] = TRUE;
  $form_state['step'] = $form_state['step'] -1;
}

function pum_expert_mycv_education_callback($form, $form_state) {
  return $form['form']['education_entries'];
}

function pum_expert_mycv_get_civi_education($contact_id) {
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
    $i = 0;
    $field_name = $fields[$value['id']]['name'];
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