<?php
/*
 * @file
 * Export Functions
 *
 */

date_default_timezone_set('America/New_York');

$library = libraries_get_path('PHPExcel');

/** Include PHPExcel */
require_once $library . '/Classes/PHPExcel.php';

function call_to_export($export){
	// Create new PHPExcel object
	$objPHPExcel = new PHPExcel();

	// Set document properties
	$objPHPExcel->getProperties()
		->setCreator("QPP REPORTS")
		->setLastModifiedBy("QPP REPORTS")
		->setTitle("Office 2007 XLSX Document")
		->setSubject("Office 2007 XLSX Document")
		->setDescription("QPP REPORTS")
		->setKeywords("office 2007 openxml php")
		->setCategory("Reports");

	$styleArray = array(
		'font'  => array(
			'bold'  => true,
			'color' => array('rgb' => '1A6FCD'),
			'size'  => 10,
			'name'  => 'arial',
			'underline' => 'single',
		)
	);
	
	if(isset($export['users_logins'])){
		$objPHPExcel->setActiveSheetIndex(0);
		$sheet_logins = $objPHPExcel->getActiveSheet(0);
		
		// set worksheet title
		$sheet_logins->setTitle($export['users_logins']['sheet1']['title']);
		
		// set report title
		$sheet_logins->getStyle('A1:z1')->getFont()->setBold(true)->setSize(16);
		$sheet_logins->mergeCells('A1:I1');
		$sheet_logins->SetCellValue('A1',$export['users_logins']['sheet1']['report_title']);
		$sheet_logins->getStyle('A2:z2')->getFont()->setBold(true)->setSize(12);
		$sheet_logins->mergeCells('A2:I2');
		$sheet_logins->SetCellValue('A2',$export['users_logins']['sheet1']['date_range']);
		
		// set column widths
		$sheet_logins->getColumnDimension('A')->setWidth(25);
		$sheet_logins->getColumnDimension('B')->setWidth(25);
		$sheet_logins->getColumnDimension('C')->setWidth(10);
		$sheet_logins->getColumnDimension('D')->setWidth(25);
		$sheet_logins->getColumnDimension('E')->setWidth(35);
		$sheet_logins->getColumnDimension('F')->setWidth(25);
		$sheet_logins->getColumnDimension('G')->setWidth(25);
		$sheet_logins->getColumnDimension('H')->setWidth(25);
		$sheet_logins->getColumnDimension('I')->setWidth(25);
		$sheet_logins->getColumnDimension('J')->setWidth(15);
		$sheet_logins->getColumnDimension('K')->setWidth(25);
		
		// set vertical alignment
		$sheet_logins->getDefaultStyle()->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_TOP);
		
		// set column horizontal alignment
		$sheet_logins->getStyle('K4:K999')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT);
		
		// set wrap text
		$sheet_logins->getStyle('C3:K999')->getAlignment()->setWrapText(true); 
		
		// set column headers
		if(isset($export['users_logins']['sheet1']['header'])){
			$col = 0;
			$row = 3; //start from row 3
			$sheet_logins->getStyle('A3:Z3')->getFont()->setBold(true);
			foreach($export['users_logins']['sheet1']['header'] as $key){
				$sheet_logins->setCellValueByColumnAndRow($col, $row, $key);
				$col++;
			}
		}
		
		// print rows
		if(isset($export['users_logins']['sheet1']['rows'])){
			$row = 4;
			foreach($export['users_logins']['sheet1']['rows'] as $rows){
				$col = 0;
				foreach ($rows as $value){
					$sheet_logins->setCellValueByColumnAndRow($col, $row, $value);
					$col++;	
				}
				$row++;
			}
		}		
		
		// new worksheet for portal login totals
		$objPHPExcel->createSheet();
		$objPHPExcel->setActiveSheetIndex(1);			
		$sheet_logins_total = $objPHPExcel->getActiveSheet(1);
		
		// set worksheet title
		$sheet_logins_total->setTitle($export['users_logins']['sheet2']['title']);
		
		// set report title
		$sheet_logins_total->getStyle('A1:z1')->getFont()->setBold(true)->setSize(16);
		$sheet_logins_total->mergeCells('A1:I1');
		$sheet_logins_total->SetCellValue('A1',$export['users_logins']['sheet2']['report_title']);
		$sheet_logins_total->getStyle('A2:z2')->getFont()->setBold(true)->setSize(12);
		$sheet_logins_total->mergeCells('A2:I2');
		$sheet_logins_total->SetCellValue('A2',$export['users_logins']['sheet2']['date_range']);
		
		// set column widths
		$sheet_logins_total->getColumnDimension('A')->setWidth(35);
		$sheet_logins_total->getColumnDimension('B')->setWidth(25);
		
		// set vertical alignment
		$sheet_logins_total->getDefaultStyle()->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_TOP);
		
		// set column headers
		if(isset($export['users_logins']['sheet2']['header'])){
			$col = 0;
			$row = 3; //start from row 3
			$sheet_logins_total->getStyle('A3:Z3')->getFont()->setBold(true);
			foreach($export['users_logins']['sheet2']['header'] as $key){
				$sheet_logins_total->setCellValueByColumnAndRow($col, $row, $key);
				$col++;
			}
		}
		
		// print rows
		if(isset($export['users_logins']['sheet2']['rows'])){
			$row = 4;
			foreach($export['users_logins']['sheet2']['rows'] as $rows){
				$col = 0;
				foreach ($rows as $value){
					$sheet_logins_total->setCellValueByColumnAndRow($col, $row, $value);
					$col++;	
				}
				$row++;
			}

			if(isset($export['users_logins']['sheet2']['rows_total'])){
				$row = $row+1;
				foreach($export['users_logins']['sheet2']['rows_total'] as $rows){
					$col = 0;
					foreach ($rows as $value){
						$sheet_logins_total->setCellValueByColumnAndRow($col, $row, $value);
						$col++;
					}
					$row++;
				}
			}		
		}
	}
	
	if(isset($export['users_interactions'])){
		$objPHPExcel->setActiveSheetIndex(0);
		$sheet_interactions = $objPHPExcel->getActiveSheet(0);
		
		// set worksheet title
		$sheet_interactions->setTitle($export['users_interactions']['sheet1']['title']);
		
		// set report title
		$sheet_interactions->getStyle('A1:z1')->getFont()->setBold(true)->setSize(16);
		$sheet_interactions->mergeCells('A1:I1');
		$sheet_interactions->SetCellValue('A1',$export['users_interactions']['sheet1']['report_title']);
		$sheet_interactions->getStyle('A2:z2')->getFont()->setBold(true)->setSize(12);
		$sheet_interactions->mergeCells('A2:I2');
		$sheet_interactions->SetCellValue('A2',$export['users_interactions']['sheet1']['date_range']);
		
		// set column widths
		$sheet_interactions->getColumnDimension('A')->setWidth(25);
		$sheet_interactions->getColumnDimension('B')->setWidth(25);
		$sheet_interactions->getColumnDimension('C')->setWidth(25);
		$sheet_interactions->getColumnDimension('D')->setWidth(25);
		$sheet_interactions->getColumnDimension('E')->setWidth(35);
		$sheet_interactions->getColumnDimension('F')->setWidth(25);
		$sheet_interactions->getColumnDimension('G')->setWidth(35);
		$sheet_interactions->getColumnDimension('H')->setWidth(25);
		$sheet_interactions->getColumnDimension('I')->setWidth(25);
		$sheet_interactions->getColumnDimension('J')->setWidth(25);
		$sheet_interactions->getColumnDimension('K')->setWidth(25);
		$sheet_interactions->getColumnDimension('L')->setWidth(25);
		$sheet_interactions->getColumnDimension('M')->setWidth(25);
		
		// set vertical alignment
		$sheet_interactions->getDefaultStyle()->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_TOP);
		
		// set column horizontal alignment
		$sheet_interactions->getStyle('M4:M999')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT);
		
		// set wrap text
		$sheet_interactions->getStyle('C3:M999')->getAlignment()->setWrapText(true); 
		
		// set column headers
		if(isset($export['users_interactions']['sheet1']['header'])){
			$col = 0;
			$row = 3; //start from row 3
			$sheet_interactions->getStyle('A3:Z3')->getFont()->setBold(true);
			foreach($export['users_interactions']['sheet1']['header'] as $key){
				$sheet_interactions->setCellValueByColumnAndRow($col, $row, $key);
				$col++;
			}
		}
		
		// print rows
		if(isset($export['users_interactions']['sheet1']['rows'])){
			$row = 4;
			foreach($export['users_interactions']['sheet1']['rows'] as $rows){
				$col = 0;
				foreach ($rows as $value){
					$sheet_interactions->setCellValueByColumnAndRow($col, $row, $value);
					$col++;	
				}
				$row++;
			}
		}		
		
		// new worksheet for portal login totals
		$objPHPExcel->createSheet();
		$objPHPExcel->setActiveSheetIndex(1);			
		$sheet_interactions_total = $objPHPExcel->getActiveSheet(1);
		
		// set worksheet title
		$sheet_interactions_total->setTitle($export['users_interactions']['sheet2']['title']);
		
		// set report title
		$sheet_interactions_total->getStyle('A1:z1')->getFont()->setBold(true)->setSize(16);
		$sheet_interactions_total->mergeCells('A1:I1');
		$sheet_interactions_total->SetCellValue('A1',$export['users_interactions']['sheet2']['report_title']);
		$sheet_interactions_total->getStyle('A2:z2')->getFont()->setBold(true)->setSize(12);
		$sheet_interactions_total->mergeCells('A2:I2');
		$sheet_interactions_total->SetCellValue('A2',$export['users_interactions']['sheet2']['date_range']);
		
		// set column widths
		$sheet_interactions_total->getColumnDimension('A')->setWidth(35);
		$sheet_interactions_total->getColumnDimension('B')->setWidth(25);
		$sheet_interactions_total->getColumnDimension('C')->setWidth(25);
		
		// set vertical alignment
		$sheet_interactions_total->getDefaultStyle()->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_TOP);
		
		// set column headers
		if(isset($export['users_interactions']['sheet2']['header'])){
			$col = 0;
			$row = 3; //start from row 3
			$sheet_interactions_total->getStyle('A3:Z3')->getFont()->setBold(true);
			foreach($export['users_interactions']['sheet2']['header'] as $key){
				$sheet_interactions_total->setCellValueByColumnAndRow($col, $row, $key);
				$col++;
			}
		}
		
		// print rows
		if(isset($export['users_interactions']['sheet2']['rows'])){
			$row = 4;
			foreach($export['users_interactions']['sheet2']['rows'] as $rows){
				$col = 0;
				foreach ($rows as $value){
					$sheet_interactions_total->setCellValueByColumnAndRow($col, $row, $value);
					$col++;	
				}
				$row++;
			}

			if(isset($export['users_interactions']['sheet2']['rows_total'])){
				$row = $row+1;
				foreach($export['users_interactions']['sheet2']['rows_total'] as $rows){
					$col = 0;
					foreach ($rows as $value){
						$sheet_interactions_total->setCellValueByColumnAndRow($col, $row, $value);
						$col++;
					}
					$row++;
				}
			}		
		}
	}
	
	$filename =  isset($export['filename']) ? $export['filename'] . ".xlsx" : "qpp_portal_report_" . date('m-d-Y_h-i') . ".xlsx";
	
	$objPHPExcel->setActiveSheetIndex(0);
	header('Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet');
	header('Content-Disposition: attachment;filename="' . $filename . '"');
	header('Cache-Control: max-age=0');

	$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
	ob_end_clean();
	$objWriter->save('php://output');

	exit;
}

?>