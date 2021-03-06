# ALL LENGTHS MUST BE GIVEN IN MILLIMETRES
# ALL ROTATIONS MUST BE GIVEN IN RADIANS

DROP DATABASE IF EXISTS MASKS;
CREATE DATABASE MASKS;
USE MASKS;

CREATE TABLE BEAMCAL_CONE (
    POSX          DOUBLE(10,3), #
    POSY          DOUBLE(10,3), #
    POSZ          DOUBLE(10,3), #
    RED           DOUBLE(10,3), #
    GREEN         DOUBLE(10,3), #
    BLUE          DOUBLE(10,3), #
    VISATT        VARCHAR(32),  # I = INVISIBLE, S = SOLID, W = WIREFRAME
    LENGTH        DOUBLE(10,3), #
    RINNERSTART   DOUBLE(10,3), #
    RINNEREND     DOUBLE(10,3), #
    ROUTERSTART   DOUBLE(10,3), #
    ROUTEREND     DOUBLE(10,3), #
    STARTPHI      DOUBLE(10,3), #
    DELTAPHI      DOUBLE(10,3), #
    ROTPSI        DOUBLE(10,3), #
    ROTTHETA      DOUBLE(10,3), #
    ROTPHI        DOUBLE(10,3), #
    MATERIAL      VARCHAR(32),  # MATERIAL, CGA LITERAL NAME
    NAME          VARCHAR(32),   # NAME OF SOLID, LOGICAL, AND PHYSICAL VOLUME
    PARENTNAME    VARCHAR(32)   # NAME OF PARENT
);
                      
INSERT INTO BEAMCAL_CONE VALUES (0.0, 0.0, 3250, 0.8, 0.2, 0.2, "S", 499, 00.0, 00.0, 120.0, 160.0,3.14, 3.14, 0., 0., 0., "Tungsten", "beamcal", ""); 

INSERT INTO BEAMCAL_CONE VALUES (32.5, 0.0, 0.0, 0.0, 1.0, 0.0, "S", 499.03, 00.0, 00.0, 12.0, 16.0, 3.14, 3.14, 0., 0., 10.e-3, "Vacuum", "beamcal_inner", "beamcal"); 


