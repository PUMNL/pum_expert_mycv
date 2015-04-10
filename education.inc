<?php

require_once('civicrm.inc');

function pum_expert_mycv_education_form(&$form_state) {
  $contact = pum_expert_mycv_get_civi_contact();
  $educations = pum_expert_mycv_get_civi_education($contact['id']);

  $form['education_info']['#type'] = 'fieldset';
  $form['education_info']['#title'] = t('Education');
  $form['education_info']['info'] = array(
    '#type' => 'markup',
    '#markup' => t('Please provide us with your relevant education and training details. Start with your education after completion of secondary school. For each additional education or training you wish to submit, click the box at the bottom of the form.'),
  );

  $form['education_entries'] = array(
    '#type' => 'markup',
    '#marpup' => '',
    '#prefix' => '<div id="entry-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (!empty($form_state['next'])) {
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
    );

    $form['education_entries']['education']['education_'.$i]['education_field_of_study_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Field of study/major'),
      '#default_value' => isset($educations[$i]['Field_of_study_major']) && !$addMorePressed ? $educations[$i]['Field_of_study_major'] : '',
    );

    $form['education_entries']['education']['education_'.$i]['education_city_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => isset($educations[$i]['City']) && !$addMorePressed ? $educations[$i]['City'] : '',
    );

    $form['education_entries']['education']['education_'.$i]['education_country_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => !empty($educations[$i]['Country']) && !$addMorePressed ? $educations[$i]['Country'] : '1152',
      '#options' => CRM_Core_PseudoConstant::country(),
    );

    $form['education_entries']['education']['education_'.$i]['education_education_level_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Education level'),
      '#default_value' => isset($educations[$i]['Education_level']) && !$addMorePressed ? $educations[$i]['Education_level'] : '',
      '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('education_level_20140825212618'),
    );

    $form['education_entries']['education']['education_'.$i]['education_years_from_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Years from'),
      '#default_value' => isset($educations[$i]['Years_From']) && !$addMorePressed ? $educations[$i]['Years_From'] : '',
      '#rules' => array(
        'numeric',
        'length[4]',
      ),
    );

    $form['education_entries']['education']['education_'.$i]['education_to_'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('Years to'),
      '#default_value' => isset($educations[$i]['To']) && !$addMorePressed ? $educations[$i]['To'] : '',
      '#rules' => array(
        'numeric',
        'length[4]',
      ),
    );

    $form['education_entries']['education']['education_'.$i]['education_diploma_degree_'.$i] = array(
      '#type' => 'select',
      '#title' => t('Diploma/Degree'),
      '#default_value' => isset($educations[$i]['Diploma_Degree']) && !$addMorePressed ? $educations[$i]['Diploma_Degree'] : '',
      '#options' => array('' => t('- None -'), '1' => t('Yes'), '0' => t('No')),
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
  );

  return array('form' => $form, 'title' => t('Education'));
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