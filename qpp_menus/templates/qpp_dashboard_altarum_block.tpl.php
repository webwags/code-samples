<?php
 global $user;
  // Check to see if $user has role.
  if(in_array('Administrator', $user->roles) OR in_array('Altarum Manager', $user->roles) OR in_array('Altarum Advisor', $user->roles)){ 
	print  '<ul class="dashboard-menu nav">
			  <li class="leaf"><a href="/dashboard/non-midwest-practices">View All Non Midwest Practices</a></li>';		   
	if(in_array('Administrator', $user->roles)){ 
	 print  '  <li class="leaf"><a href="/dashboard/all-advisors">Manage All Advisors</a></li>
	 		   <li class="leaf"><a href="/dashboard/manage-states">Manage States</a></li>
	  		   <li class="leaf"><a href="/dashboard/manage-practices">Change Practices Status</a></li>
	 		   <li class="leaf"><a href="/dashboard/manage-sdos">Manage SDOs</a></li>
	 		   <li class="last leaf"><a href="/admin/structure/taxonomy/service_delivery_organizations/add">Add SDO</a></li>
			   <li class="leaf"><a href="/admin/structure/taxonomy/tags">Manage Tags</a></li>
	 		   <li class="last leaf"><a href="/admin/structure/taxonomy/tags/add">Add Tags</a></li>
	 		   <li class="leaf"><a href="/dashboard/manage-contract-types">Manage Commercial Contract Types</a></li>
	 		   <li class="last leaf"><a href="/admin/structure/taxonomy/commercial_contract_type/add">Add Commercial Contract Type</a></li>';
}
     print  '  <li class="leaf"><a href="/dashboard/reports">Download Reports</a></li>
               <li class="last leaf"><a href="/dashboard/list-of-practices-export"><span class="btn btn-success-sm">Download All Practices</span></a></li>
            </ul>';
	
	
  }
?>