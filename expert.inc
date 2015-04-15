<?php


require_once('civicrm.inc');
require_once('education.inc');
require_once('workhistory.inc');

function expert_cv($form, &$form_state) {

  if(isset($form_state['values'])) {
    $currstep = $form_state['step'] + 1;
  }else {
    $currstep = 0;
  }
  $form_state['step'] = $currstep;
  $allsteps = expert_cv_get_forms($form_state, $currstep);
  $currform['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>'.$allsteps[$currstep]['title'].' ('.($currstep+1).'/'.count($allsteps).')</h2>',
  );
  $currform['form'] =  $allsteps[$currstep]['form'];

  if (($currstep+1) > 1) {
    $currform['previous']['#type'] = 'submit';
    $currform['previous']['#value'] = t('Previous');
    $currform['previous']['#submit'] = array('expert_cv_previous');
    $currForm['previous']['#limit_validation_errors'] = array();
  }

  if (($currstep+1) == count($allsteps)) {
    $currform['next']['#type'] = 'submit';
    $currform['next']['#value'] = t('Submit');
  } else {
    $currform['next']['#type'] = 'submit';
    $currform['next']['#value'] = t('Next');
  }

  $form_state['next'] = false;

  return $currform;
}

function expert_cv_previous($form, &$form_state) {
  $form_state['step'] = $form_state['step'] - 2;
  $form_state['rebuild'] = TRUE;
}

function expert_cv_submit($form, &$form_state) {
  $form_state['storedvalues'][$form_state['step']] = $form_state['values'];
  if($form_state['step'] + 1 != count(expert_cv_get_forms($form_state, $form_state['step']))) {
    $form_state['next'] = true;
    $form_state['rebuild'] = TRUE;
  }else {
    //store the form
    $session = CRM_Core_Session::singleton();
    $contact['id'] = $session->get('userID');
    $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('expert_data::side_activities')] = $form_state['storedvalues'][0]['side_activities'];
    civicrm_api3('Contact', 'create', $contact);

    //update education
    pum_expert_mycv_civi_save_education($contact['id'], $form_state['storedvalues'][1], $form_state['num_educations']);

    //update work history
    pum_expert_mycv_civi_save_workhistory($contact['id'], $form_state['storedvalues'][2], $form_state['num_workhistory']);

    drupal_set_message(t('Your CV is successfully updated'));
    $form_state['redirect'] = 'expert/my-cv';
  }
}

function expert_cv_get_forms(&$form_state, $currstep) {
  $return[0] = expert_cv_additional_details($form_state, $currstep == 0 ? true : false);
  $return[1] = pum_expert_mycv_education_form($form_state, $currstep == 1 ? true : false);
  $return[2] = pum_expert_mycv_workhistory_form($form_state, $currstep == 2 ? true : false);
  return $return;
}


function expert_cv_additional_details(&$form_state, $rebuild) {
  $contact = pum_expert_mycv_get_civi_contact();
  $form = array();

  $form['other']['#type'] = 'fieldset';
  $form['other']['#title'] = t('Other information');

  $form['other']['side_activities'] = array(
    '#type' => 'textarea',
    '#title' => t('Professional affiliation and side activities '),
    '#default_value' => $contact['expert_data::side_activities'],
  );

  return array('form' => $form, 'title' => t('Additional details'));
}