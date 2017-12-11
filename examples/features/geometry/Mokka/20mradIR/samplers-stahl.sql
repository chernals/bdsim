# ALL LENGTHS MUST BE GIVEN IN MILLIMETRES
# ALL ROTATIONS MUST BE GIVEN IN RADIANS

DROP DATABASE IF EXISTS SAMPLE;
CREATE DATABASE SAMPLE;
USE SAMPLE;

CREATE TABLE IR_SAMPLER (
    POSX          DOUBLE(10,3), #
    POSY          DOUBLE(10,3), #
    POSZ          DOUBLE(10,3), #
    RED           DOUBLE(10,3), #
    GREEN         DOUBLE(10,3), #
    BLUE          DOUBLE(10,3), #
    VISATT        VARCHAR(32),  # I = INVISIBLE, S = SOLID, W = WIREFRAME
    LENGTH        DOUBLE(10,3), #
    ROUTERSTART   DOUBLE(10,3), #
    ROUTEREND     DOUBLE(10,3), #
    ROTPSI        DOUBLE(10,3), #
    ROTTHETA      DOUBLE(10,3), #
    ROTPHI        DOUBLE(10,3), #
    MATERIAL      VARCHAR(32),  # MATERIAL, CGA LITERAL NAME
    NAME          VARCHAR(32)   # NAME OF SOLID, LOGICAL, AND PHYSICAL VOLUME
);
                      
INSERT INTO IR_SAMPLER VALUES (0.0, 0.0, 3000.25, 1.0, 1.0, 1.0, "S", 1e-8, 120, 120, 0., 0., 0.0, "Vacuum", ""); 
INSERT INTO IR_SAMPLER VALUES (0.0, 0.0, 3499.75, 1.0, 1.0, 1.0, "S", 1e-8, 160, 160, 0., 0., 0.0, "Vacuum", ""); 

