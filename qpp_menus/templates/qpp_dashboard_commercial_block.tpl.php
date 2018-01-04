

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
  if ($sdoCheck0TID ==  457 || $sdoCheck1TID ==  457) {
		print  '<ul class="dashboard-menu nav">
              <li class="leaf"><a href="/dashboard/all-commercial-practices-in-queue">View Commercial Practices in the Queue</a></li>
              <li class="leaf"><a href="/dashboard/all-commercial-practices">View All Commercial Practices</a></li>
              <li class="leaf"><a href="/user/commercial-registration">Add a Commercial Only Practice</a></li>
            </ul>';
	
	}
}
?>
