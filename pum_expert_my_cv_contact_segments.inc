<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class pum_expert_my_cv_contact_segments {
    /**
     * Function to get sector coordinator from customer
     * 
     * @param int $contact_id
     * @return array $sector_coordinators
     * @access protected
     * @static
     */
    public static function get_sector_coordinators($contact_id) {
        $sector_coordinators = array();
        $sectors = self::get_sectors($contact_id);
        foreach ($sectors as $segment_id => $segment) {
            $sector_coordinators[$segment_id] = civicrm_api3('ContactSegment', 'Getvalue', array(
              'is_active' => 1,
              'role_value' => 'Sector Coordinator',
              'segment_id' => $segment_id,
              'return' => 'contact_id'));
        }
        return $sector_coordinators;
    }

    /**
     * Function to get sector from expert
     *
     * @param int $contact_id
     * @return array
     * @access protected
     * @static
     */
    public static function get_sectors($contact_id) {
      $sectors = array();
      $contact_segments = civicrm_api3('ContactSegment', 'Get',
        array('contact_id' => $contact_id, 'is_active' => 1, 'role_value' => 'Expert'));
      foreach ($contact_segments['values'] as $contact_segment_id => $contact_segment) {
        $segment = civicrm_api3('Segment', 'Getsingle', array('id' => $contact_segment['segment_id']));
        if (empty($segment['parent_id'])) {
          $sectors[$segment['id']] = $segment['label'];
        }
    }
      return $sectors;
    }

    public static function get_areas_of_expertise($contact_id) {
      $areas_of_expertises = array();
      $contact_segments = civicrm_api3('ContactSegment', 'Get',
        array('contact_id' => $contact_id, 'is_active' => 1, 'role_value' => 'Expert'));
      foreach ($contact_segments['values'] as $contact_segment_id => $contact_segment) {
        $segment = civicrm_api3('Segment', 'Getsingle', array('id' => $contact_segment['segment_id']));
        if (!empty($segment['parent_id'])) {
          $parent_label = civicrm_api3('Segment', 'Getvalue',
            array('id' => $segment['parent_id'], 'return' => 'label'));
          $areas_of_expertises[$segment['id']] = "(sector: ".$parent_label.") ".$segment['label'];
        }
      }
      return $areas_of_expertises;
    }
}
