<?php

  $epsg = array(
    array(   '1',  '27391' ),
    array(   '2',  '27392' ),
    array(   '3',  '27393' ),
    array(   '4',  '27394' ),
    array(   '5',  '27395' ),
    array(   '6',  '27396' ),
    array(   '7',  '27397' ),
    array(   '8',  '27398' ),
    array(   '9',   '4817' ),
    array(  '59',  '32629' ),
    array(  '60',  '32630' ),
    array(  '61',  '32631' ),
    array(  '62',  '32632' ),
    array(  '63',  '32633' ),
    array(  '64',  '32634' ),
    array(  '65',  '32635' ),
    array(  '66',  '32636' ),
    array( '184',   '4326' ),
    array(  '31',  '23031' ),
    array(  '32',  '23032' ),
    array(  '33',  '23033' ),
    array(  '34',  '23034' ),
    array(  '35',  '23035' ),
    array(  '36',  '23036' ),
    array(  '19',  '25829' ),
    array(  '20',  '25830' ),
    array(  '21',  '25831' ),
    array(  '22',  '25832' ),
    array(  '23',  '25833' ),
    array(  '24',  '25834' ),
    array(  '25',  '25835' ),
    array(  '26',  '25836' ),
    array(  '84',   '4258' ),
    array(  '73',   '3035' ),
    array(  '74',   '3034' ) );
  
  $urlFmt = 'http://spatialreference.org/ref/epsg/%s/prj/';
  foreach( $epsg as $sys ) {
    $filename = $sys[ 1 ] . '.prj';
    if( file_exists( $filename ) ) {
      $prjStr = file_get_contents( $filename );
    }
    else {
      $prjStr = file_get_contents( sprintf( $urlFmt, $sys[ 1 ] ) );
      file_put_contents( $filename, $prjStr );
    }
    preg_match( '/(PROJCS|GEOGCS)\[\\"([^\\"]*)/i', $prjStr, $m );
    printf( "coordSysTable[ %s ] = CoordSys( %s, \"%s\", \"%s\" );\n", $sys[ 0 ], $sys[ 0 ], $m[ 2 ], addslashes( $prjStr ) );
  }

  
  
?>