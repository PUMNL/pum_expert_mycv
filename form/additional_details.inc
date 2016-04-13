<?php

/**
 * Implements hook_form().
 *
 * Build the form to store the side activities fields.
 *
 * @param $form
 * @param $form_state
 * @param $contact_id
 * @param null $id
 * @return mixed
 */
function expert_cv_additional_details_form($form, &$form_state) {
  civicrm_initialize();

  $contact = pum_expert_mycv_get_civi_contact();
  $values = array();
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  $form['other']['#type'] = 'fieldset';
  $form['other']['#title'] = t('Other information');

  $form['other']['side_activities'] = array(
    '#type' => 'textarea',
    '#title' => t('Professional affiliation and side activities '),
    '#field_suffix' => '<code class="help">In case it could be relevant for PUM projects</code>',
    '#default_value' => pum_expert_mycv_value($values, $contact, 'side_activities', 'expert_data::side_activities'),
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

function expert_cv_additional_details_form_submit($form, &$form_state) {
  global $user;
  civicrm_initialize();
  //store the form
  $session = CRM_Core_Session::singleton();
  $contact['id'] = $session->get('userID');
  $contact['custom_'._pum_expert_mycv_get_custom_field_id_by_name('expert_data::side_activities')] = $form_state['values']['side_activities'];
  civicrm_api3('Contact', 'create', $contact);

  drupal_set_message(t('Your CV is successfully updated'));
  if (in_array("Expert", $user->roles)) {
    $form_state['redirect'] = 'expert/my-cv';
  } elseif (in_array("Candidate expert", $user->roles)) {
    $form_state['redirect'] = 'portal';
  }
}