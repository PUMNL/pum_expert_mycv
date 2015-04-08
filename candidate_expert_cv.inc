<?php

require_once('civicrm.inc');

function candidate_expert_cv($form, &$form_state) {

  if(isset($form_state['values'])) {
    $currstep = $form_state['step'] + 1;
  }else {
    $currstep = 0;
  }
  $form_state['step'] = $currstep;
  $allsteps = candidate_expert_cv_get_forms();
  $currform =  $allsteps[$currstep];

  return $currform;
}

function candidate_expert_cv_submit($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  if($form_state['step'] + 1 != count(candidate_expert_cv_get_forms())) {
    $form_state['rebuild'] = TRUE;
  }else {
    //store the form
    $session = CRM_Core_Session::singleton();
    $contact['id'] = $session->get('userID');
    $contact['prefix_id'] = $form_state['storedvalues'][0]['prefix'];
    $contact['first_name'] = $form_state['storedvalues'][0]['first_name'];
    $contact['middle_name'] = $form_state['storedvalues'][0]['middle_name'];
    $contact['last_name'] = $form_state['storedvalues'][0]['last_name'];
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('Additional_Data::Initials')] = $form_state['storedvalues'][0]['initials'];
    civicrm_api3('Contact', 'create', $contact);

    drupal_set_message(t('Your CV is successfully updated'));
    $form_state['redirect'] = 'portal';
  }
}

function candidate_expert_cv_get_forms() {
  return array(
    candidate_expert_cv_contact_details(),
  );
}

function candidate_expert_cv_contact_details() {
  $contact = pum_expert_mycv_get_civi_contact();

  $form['contact_information']['#type'] = 'fieldset';
  $form['contact_information']['#title'] = t('Contact information');
  $form['contact_information']['prefix'] = array(
    '#type' => 'select',
    '#title' => t('Prefix'),
    '#options' => array('' => t('- None -')) + CRM_Core_OptionGroup::values('individual_prefix'),
    '#default_value' => $contact['prefix_id'],
  );
  $form['contact_information']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => $contact['first_name'],
  );
  $form['contact_information']['middle_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name'),
    '#default_value' => $contact['middle_name'],
  );
  $form['contact_information']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => $contact['last_name'],
  );

  $form['contact_information']['initials'] = array(
    '#type' => 'textfield',
    '#title' => t('Initials'),
    '#default_value' => $contact['Additional_Data::Initials'],
  );

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Next');

  return $form;
}