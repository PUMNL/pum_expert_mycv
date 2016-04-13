<?php

require_once('candidate_expert_cv.inc');

function pum_expert_mycv_menu() {
  $items = array();
  $items['candidate-expert-cv'] = array( //this creates a URL that will call this form at "examples/form-example"
    'title' => t('Candidate Expert PUM CV'), //page title
    'description' => '',
    'page callback' => 'drupal_get_form', //this is the function that will be called when the page is accessed.  for a form, use drupal_get_form
    'page arguments' => array('candidate_expert_cv', 3), //put the name of the form here
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'menu_name' => 'menu-my-profile',
  );

  $items['expert/additional-details'] = array(
    'title' => t('Edit additional details'),
    'description' => '',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('expert_cv_additional_details_form'),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/additional_details.inc',
  );

  $items['expert/cv-edit-workhistory/%/%'] = array(
    'title' => t('Edit workhistory'),
    'description' => '',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('expert_cv_workhistory', 2, 3),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/workhistory.inc',
  );

  $items['expert/cv-edit-workhistory/%/%/delete'] = array(
    'title' => t('Remove workhistory'),
    'description' => '',
    'page callback' => 'expert_cv_workhistory_remove',
    'page arguments' => array(2, 3),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/workhistory.inc',
  );

  $items['expert/cv-edit-workhistory/%/%/switch/%'] = array(
    'title' => t('Switch workhistory'),
    'description' => '',
    'page callback' => 'expert_cv_workhistory_switch',
    'page arguments' => array(2, 3,5),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/workhistory.inc',
  );

  $items['expert/cv-edit-workhistory/%/add'] = array(
    'title' => t('Add workhistory'),
    'description' => '',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('expert_cv_workhistory', 2),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/workhistory.inc',
  );

  $items['expert/cv-edit-education/%/%'] = array(
    'title' => t('Edit education'),
    'description' => '',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('expert_cv_education', 2, 3),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/education.inc',
  );

  $items['expert/cv-edit-education/%/%/delete'] = array(
    'title' => t('Remove education'),
    'description' => '',
    'page callback' => 'expert_cv_education_remove',
    'page arguments' => array(2, 3),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/education.inc',
  );

  $items['expert/cv-edit-education/%/%/switch/%'] = array(
    'title' => t('Switch education'),
    'description' => '',
    'page callback' => 'expert_cv_education_switch',
    'page arguments' => array(2, 3,5),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/education.inc',
  );

  $items['expert/cv-edit-education/%/add'] = array(
    'title' => t('Add education'),
    'description' => '',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('expert_cv_education', 2),
    'access callback' => '_pum_expert_mycv_user_has_role',
    'access arguments' => array(array('Expert', 'Candidate expert')), // arg 1 loads the user, arg 2 is the role name
    'file' => 'form/education.inc',
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