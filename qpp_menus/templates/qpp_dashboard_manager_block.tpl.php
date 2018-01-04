<?php
  global $user;
  // Check to see if $user has role.
  if(in_array('Administrator', $user->roles) OR in_array('Altarum Manager', $user->roles) OR in_array('QPP Manager', $user->roles)){ 
	print  '<ul class="dashboard-menu nav">
              <li class="leaf"><a href="/admin/people/create?destination=dashboard/my-advisors">Add Advisor</a></li>
              <li class="leaf"><a href="/dashboard/my-advisors">Manage My Advisors</a></li>
            </ul>';
	
}
?>