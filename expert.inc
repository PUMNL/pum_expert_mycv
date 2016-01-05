<?php


require_once('civicrm.inc');
require_once('education.inc');
require_once('workhistory.inc');

function expert_cv($form, &$form_state) {

  if(!isset($form_state['step'])) {
    $form_state['step'] = 0;
  }
  $current_step = $form_state['step'];
  $step_count = expert_cv_get_form_count();

  $current_form = expert_cv_get_form($form_state, $current_step, $step_count);
  $return['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>'.$current_form['title'].' ('.($current_step+1).'/'.$step_count.')</h2>',
  );
  $currform['form'] =  $current_form['form'];

  $path = drupal_get_path('module', 'pum_portal_webform_help');
  drupal_add_js($path . '/ppwh.js');
  drupal_add_css($path . '/ppwh.css');

  return $currform;
}

function expert_cv_get_form_count() {
  return 3;
}

function expert_cv_get_form(&$form_state, $current_step, $step_count) {
  switch($current_step) {
    case 0:
      $form = pum_expert_mycv_education_form($form_state, 'expert_cv');
      unset($form['form']['previous']);
      return $form;
      break;
    case 1:
      return pum_expert_mycv_workhistory_form($form_state, 'expert_cv');
      break;
    case 2:
      return expert_cv_additional_details($form_state);
      break;
  }

  throw new Exception('Current step in form not found');
}

function expert_cv_previous($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['input'];
  $form_state['step'] = $form_state['step'] - 1;
  $form_state['values'] = $form_state['storedvalues'][$form_state['step']];
  $form_state['next'] = false;
  $form_state['previous'] = true;
  $form_state['rebuild'] = TRUE;
}

function expert_cv_next($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  $form_state['step'] = $form_state['step'] + 1;
  if (isset($form_state['storedvalues'][$form_state['step']])) {
    $form_state['values'] = $form_state['storedvalues'][$form_state['step']];
  }
  $form_state['next'] = true;
  $form_state['previous'] = false;
  $form_state['rebuild'] = TRUE;
}

function expert_cv_validate($form, &$form_state) {
  if (form_get_errors()) {
    $path = drupal_get_path('module', 'pum_portal_webform_help');
    drupal_add_js($path . '/ppwh.js');
    drupal_add_css($path . '/ppwh.css');
  }
}

function expert_cv_submit($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  civicrm_initialize();
  //store the form
  $session = CRM_Core_Session::singleton();
  $contact['id'] = $session->get('userID');
  $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('expert_data::side_activities')] = $form_state['storedvalues'][2]['side_activities'];
  civicrm_api3('Contact', 'create', $contact);

  //update education
  pum_expert_mycv_civi_save_education($contact['id'], $form_state['storedvalues'][0], $form_state['num_educations']);

  //update work history
  pum_expert_mycv_civi_save_workhistory($contact['id'], $form_state['storedvalues'][1], $form_state['num_workhistory']);

  drupal_set_message(t('Your CV is successfully updated'));
  $form_state['redirect'] = 'expert/my-cv';
}


function expert_cv_additional_details(&$form_state) {
  $contact = pum_expert_mycv_get_civi_contact();

  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form = array();

  $form['other']['#type'] = 'fieldset';
  $form['other']['#title'] = t('Other information');

  $form['other']['side_activities'] = array(
    '#type' => 'textarea',
    '#title' => t('Professional affiliation and side activities '),
    '#field_suffix' => '<code class="help">In case it could be relevant for PUM projects</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'side_activities', 'expert_data::side_activities'),
  );

  $form['previous']['#type'] = 'submit';
  $form['previous']['#value'] = t('Previous');
  $form['previous']['#submit'] = array('expert_cv_previous');
  $form['previous']['#limit_validation_errors'] = array();
  $form['previous']['#validate'] = array();

  $form['next']['#type'] = 'submit';
  $form['next']['#value'] = t('Submit');
  $form['next']['#validate'] =array();

  return array('form' => $form, 'title' => t('Additional details'));
}