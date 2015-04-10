<?php

require_once('candidate_expert_cv.inc');
require_once('expert.inc');

function pum_expert_mycv_menu() {
  $items = array();
  $items['candidate-expert-cv'] = array( //this creates a URL that will call this form at "examples/form-example"
    'title' => t('Candidate Expert PUM CV'), //page title
    'description' => '',
    'page callback' => 'drupal_get_form', //this is the function that will be called when the page is accessed.  for a form, use drupal_get_form
    'page arguments' => array('candidate_expert_cv', 3), //put the name of the form here
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'menu_name' => 'navigation',
  );

  $items['expert/my-cv/edit'] = array( //this creates a URL that will call this form at "examples/form-example"
    'title' => t('Edit my PUM CV'), //page title
    'description' => '',
    'page callback' => 'drupal_get_form', //this is the function that will be called when the page is accessed.  for a form, use drupal_get_form
    'page arguments' => array('expert_cv', 3), //put the name of the form here
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert')), // arg 1 loads the user, arg 2 is the role name
  );

  return $items;
}

function _pum_expert_mycv_user_has_role($roles = array()) {
  global $user;
  foreach ($roles as $role) {
    if (in_array($role, $user->roles)) {
      return TRUE;
    }
  }
  return FALSE;
}