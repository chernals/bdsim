# ALL LENGTHS MUST BE GIVEN IN MILLIMETRES
# ALL ROTATIONS MUST BE GIVEN IN RADIANS

DROP DATABASE IF EXISTS INVSAMPLE;
CREATE DATABASE INVSAMPLE;
USE INVSAMPLE;

CREATE TABLE INVIR_SAMPLER (
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
                      
# inner parallel part, next to IP
INSERT INTO INVIR_SAMPLER VALUES (3000e-3, 0.0, 3000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3100e-3, 0.0, 3100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3200e-3, 0.0, 3200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3300e-3, 0.0, 3300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3400e-3, 0.0, 3400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3500e-3, 0.0, 3500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3600e-3, 0.0, 3600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3700e-3, 0.0, 3700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3800e-3, 0.0, 3800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (3900e-3, 0.0, 3900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4000e-3, 0.0, 4000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4100e-3, 0.0, 4100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4200e-3, 0.0, 4200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4300e-3, 0.0, 4300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4400e-3, 0.0, 4400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4500e-3, 0.0, 4500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4600e-3, 0.0, 4600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4700e-3, 0.0, 4700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4800e-3, 0.0, 4800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (4900e-3, 0.0, 4900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5000e-3, 0.0, 5000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5100e-3, 0.0, 5100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5200e-3, 0.0, 5200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5300e-3, 0.0, 5300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5400e-3, 0.0, 5400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5500e-3, 0.0, 5500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5600e-3, 0.0, 5600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5700e-3, 0.0, 5700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5800e-3, 0.0, 5800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (5900e-3, 0.0, 5900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6000e-3, 0.0, 6000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6100e-3, 0.0, 6100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6200e-3, 0.0, 6200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6300e-3, 0.0, 6300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6400e-3, 0.0, 6400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6500e-3, 0.0, 6500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6600e-3, 0.0, 6600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6700e-3, 0.0, 6700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6800e-3, 0.0, 6800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (6900e-3, 0.0, 6900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7000e-3, 0.0, 7000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7100e-3, 0.0, 7100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7200e-3, 0.0, 7200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7300e-3, 0.0, 7300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7400e-3, 0.0, 7400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7500e-3, 0.0, 7500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7600e-3, 0.0, 7600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7700e-3, 0.0, 7700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7800e-3, 0.0, 7800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (7900e-3, 0.0, 7900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8000e-3, 0.0, 8000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8100e-3, 0.0, 8100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8200e-3, 0.0, 8200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8300e-3, 0.0, 8300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8400e-3, 0.0, 8400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8500e-3, 0.0, 8500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8600e-3, 0.0, 8600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8700e-3, 0.0, 8700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8800e-3, 0.0, 8800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (8900e-3, 0.0, 8900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9000e-3, 0.0, 9000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9100e-3, 0.0, 9100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9200e-3, 0.0, 9200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9300e-3, 0.0, 9300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9400e-3, 0.0, 9400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9500e-3, 0.0, 9500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9600e-3, 0.0, 9600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9700e-3, 0.0, 9700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9800e-3, 0.0, 9800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (9900e-3, 0.0, 9900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10000e-3, 0.0, 10000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10100e-3, 0.0, 10100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10200e-3, 0.0, 10200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10300e-3, 0.0, 10300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10400e-3, 0.0, 10400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10500e-3, 0.0, 10500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10600e-3, 0.0, 10600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10700e-3, 0.0, 10700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10800e-3, 0.0, 10800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (10900e-3, 0.0, 10900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11000e-3, 0.0, 11000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11000e-3, 0.0, 11000, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11100e-3, 0.0, 11100, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11200e-3, 0.0, 11200, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11300e-3, 0.0, 11300, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11400e-3, 0.0, 11400, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11500e-3, 0.0, 11500, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11600e-3, 0.0, 11600, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11700e-3, 0.0, 11700, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11800e-3, 0.0, 11800, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11900e-3, 0.0, 11900, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
INSERT INTO INVIR_SAMPLER VALUES (11990e-3, 0.0, 11990, 1.0, 1.0, 1.0, "S", 1e-8, 335, 335, 0., 0., -1e-3, "VACUUM", ""); 
