<?php
 global $user;
 $advisor = user_load($user->uid); 
 $sdoTID = $advisor->field_sdo['und'][0]['tid'];
 
if(isset($sdoTID)){
$sdoTerm = taxonomy_term_load($sdoTID); 
}
$sdoCheck0TID = (isset($sdoTerm->field_sdo_type['und'][0]['tid']))?$sdoTerm->field_sdo_type['und'][0]['tid']:'';
$sdoCheck1TID = (isset($sdoTerm->field_sdo_type['und'][1]['tid']))?$sdoTerm->field_sdo_type['und'][1]['tid']:'';

if(in_array('Administrator', $user->roles) OR in_array('Altarum Manager', $user->roles) OR in_array('Altarum Advisor', $user->roles) OR in_array('QPP Manager', $user->roles) OR in_array('QPP Advisor', $user->roles)){ 
  if ($sdoCheck0TID ==  456 || $sdoCheck1TID ==  456) {
	print  '<ul class="dashboard-menu nav">
              <li class="leaf"><a href="/dashboard/all-grant-practices-in-queue">View Grant Practices in the Queue</a></li>
              <li class="leaf"><a href="/dashboard/all-grant-practices">View All Grant Practices</a></li>
            </ul>';
	
	}
}
?>




