USE mysql;

INSERT INTO user VALUES ('192.168.106.%','cqmicuser', '','Y','N','N','N','N','N','N','N','N','N','N','N','N','N');
INSERT INTO user VALUES ('192.168.106.%','cqmicadmin','','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y');

UPDATE user SET Password=PASSWORD('buratino') WHERE user='cqmicadmin';

FLUSH PRIVILEGES;
