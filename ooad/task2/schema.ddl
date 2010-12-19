ALTER TABLE "S_0"."T_VideoMedium" DROP CONSTRAINT "FK_T_VideoMedium5"
/
ALTER TABLE "S_0"."T_VideoMedium" DROP CONSTRAINT "FK_T_VideoMedium3"
/
ALTER TABLE "S_0"."T_VideoMedium" DROP CONSTRAINT "FK_T_VideoMedium2"
/
ALTER TABLE "S_0"."T_Worker" DROP CONSTRAINT "FK_T_Worker9"
/
ALTER TABLE "S_0"."T_MovieRequest" DROP CONSTRAINT "FK_T_MovieRequest4"
/
ALTER TABLE "S_0"."T_MovieRequest" DROP CONSTRAINT "FK_T_MovieRequest1"
/
ALTER TABLE "S_0"."T_RentalRecord" DROP CONSTRAINT "FK_T_RentalRecord0"
/
ALTER TABLE "S_0"."T_RentalRecord" DROP CONSTRAINT "FK_T_RentalRecord8"
/
ALTER TABLE "S_0"."T_RentalRecord" DROP CONSTRAINT "FK_T_RentalRecord7"
/
ALTER TABLE "S_0"."T_WarningMessageRecord" DROP CONSTRAINT "FK_T_WarningMessageRecord6"
/
DROP TABLE "S_0"."T_SystemUser"
/
DROP TABLE "S_0"."T_Movie"
/
DROP TABLE "S_0"."T_VideoMedium"
/
DROP TABLE "S_0"."T_RecordingType"
/
DROP TABLE "S_0"."T_Worker"
/
DROP TABLE "S_0"."T_MovieRequest"
/
DROP TABLE "S_0"."T_MediumType"
/
DROP TABLE "S_0"."T_Client"
/
DROP TABLE "S_0"."T_RentalRecord"
/
DROP TABLE "S_0"."T_WarningMessageRecord"
/
CREATE TABLE "S_0"."T_MediumType" (
	"id" NUMBER ( 20 ) NOT NULL,
	"name" VARCHAR2 ( 255 ) NOT NULL,
	CONSTRAINT "PK_T_MediumType1" PRIMARY KEY ("id")
	)
/
CREATE TABLE "S_0"."T_Worker" (
	"name" VARCHAR2 ( 255 ) NOT NULL,
	"id" NUMBER ( 20 ) NOT NULL,
	"T_SystemUser_id" NUMBER ( 20 ) NOT NULL,
	CONSTRAINT "PK_T_Worker9" PRIMARY KEY ("T_SystemUser_id", "id")
	)
/
CREATE INDEX "S_0"."TC_T_Worker19" ON "S_0"."T_Worker" ("T_SystemUser_id" )
/
CREATE TABLE "S_0"."T_RentalRecord" (
	"id" NUMBER ( 20 ) NOT NULL,
	"startTime" DATE NOT NULL,
	"estimatedFinishTime" DATE NOT NULL,
	"realFinishTime" DATE NOT NULL,
	"isReturned" NUMBER ( 1 ) NOT NULL,
	"barcode" NUMBER ( 20 ) NOT NULL,
	"T_VideoMedium_barcode" NUMBER ( 20 ) NOT NULL,
	"T_Worker_id" NUMBER ( 20 ) NOT NULL,
	"T_SystemUser_id" NUMBER ( 20 ) NOT NULL,
	CONSTRAINT "PK_T_RentalRecord5" PRIMARY KEY ("barcode", "id")
	)
/
CREATE INDEX "S_0"."TC_T_RentalRecord12" ON "S_0"."T_RentalRecord" ("barcode" )
/
CREATE INDEX "S_0"."TC_T_RentalRecord13" ON "S_0"."T_RentalRecord" ("T_SystemUser_id" , "T_Worker_id" )
/
CREATE INDEX "S_0"."TC_T_RentalRecord14" ON "S_0"."T_RentalRecord" ("T_VideoMedium_barcode" )
/
CREATE TABLE "S_0"."T_WarningMessageRecord" (
	"time" DATE NOT NULL,
	"id" NUMBER ( 20 ) NOT NULL,
	"barcode" NUMBER ( 20 ) NOT NULL,
	"T_RentalRecord_id" NUMBER ( 20 ) NOT NULL,
	CONSTRAINT "PK_T_WarningMessageRecord8" PRIMARY KEY ("barcode", "T_RentalRecord_id", "id")
	)
/
CREATE INDEX "S_0"."TC_T_WarningMessageRecord18" ON "S_0"."T_WarningMessageRecord" ("barcode" , "T_RentalRecord_id" )
/
CREATE TABLE "S_0"."T_Movie" (
	"id" NUMBER ( 20 ) NOT NULL,
	"name" VARCHAR2 ( 255 ) NOT NULL,
	CONSTRAINT "PK_T_Movie2" PRIMARY KEY ("id")
	)
/
CREATE TABLE "S_0"."T_SystemUser" (
	"id" NUMBER ( 20 ) NOT NULL,
	"login" VARCHAR2 ( 255 ) NOT NULL,
	"password" VARCHAR2 ( 255 ) NOT NULL,
	CONSTRAINT "PK_T_SystemUser6" PRIMARY KEY ("id")
	)
/
CREATE TABLE "S_0"."T_RecordingType" (
	"id" NUMBER ( 20 ) NOT NULL,
	"name" VARCHAR2 ( 255 ) NOT NULL,
	CONSTRAINT "PK_T_RecordingType4" PRIMARY KEY ("id")
	)
/
CREATE TABLE "S_0"."T_VideoMedium" (
	"barcode" NUMBER ( 20 ) NOT NULL,
	"id" NUMBER ( 20 ) NOT NULL,
	"T_Movie_id" NUMBER ( 20 ) NOT NULL,
	"T_RecordingType_id" NUMBER ( 20 ) NOT NULL,
	CONSTRAINT "PK_T_VideoMedium7" PRIMARY KEY ("barcode")
	)
/
CREATE INDEX "S_0"."TC_T_VideoMedium15" ON "S_0"."T_VideoMedium" ("T_RecordingType_id" )
/
CREATE INDEX "S_0"."TC_T_VideoMedium17" ON "S_0"."T_VideoMedium" ("id" )
/
CREATE INDEX "S_0"."TC_T_VideoMedium16" ON "S_0"."T_VideoMedium" ("T_Movie_id" )
/
CREATE TABLE "S_0"."T_Client" (
	"barcode" NUMBER ( 20 ) NOT NULL,
	"email" VARCHAR2 ( 255 ) NOT NULL,
	"evil" NUMBER ( 1 ) NOT NULL,
	"phone number" VARCHAR2 ( 255 ) NOT NULL,
	"address" VARCHAR2 ( 255 ) NOT NULL,
	CONSTRAINT "PK_T_Client0" PRIMARY KEY ("barcode")
	)
/
CREATE TABLE "S_0"."T_MovieRequest" (
	"id" NUMBER ( 20 ) NOT NULL,
	"satisfied" NUMBER ( 1 ) NOT NULL,
	"name" VARCHAR2 ( 255 ) NOT NULL,
	"barcode" NUMBER ( 20 ) NOT NULL,
	"T_Movie_id" NUMBER ( 20 ) NOT NULL,
	CONSTRAINT "PK_T_MovieRequest3" PRIMARY KEY ("barcode", "id")
	)
/
CREATE INDEX "S_0"."TC_T_MovieRequest10" ON "S_0"."T_MovieRequest" ("T_Movie_id" )
/
CREATE INDEX "S_0"."TC_T_MovieRequest11" ON "S_0"."T_MovieRequest" ("barcode" )
/
ALTER TABLE "S_0"."T_VideoMedium" ADD ( CONSTRAINT "FK_T_VideoMedium5" FOREIGN KEY ("T_RecordingType_id") REFERENCES "S_0"."T_RecordingType" ("id"))
/
ALTER TABLE "S_0"."T_VideoMedium" ADD ( CONSTRAINT "FK_T_VideoMedium3" FOREIGN KEY ("T_Movie_id") REFERENCES "S_0"."T_Movie" ("id"))
/
ALTER TABLE "S_0"."T_VideoMedium" ADD ( CONSTRAINT "FK_T_VideoMedium2" FOREIGN KEY ("id") REFERENCES "S_0"."T_MediumType" ("id"))
/
ALTER TABLE "S_0"."T_Worker" ADD ( CONSTRAINT "FK_T_Worker9" FOREIGN KEY ("T_SystemUser_id") REFERENCES "S_0"."T_SystemUser" ("id"))
/
ALTER TABLE "S_0"."T_MovieRequest" ADD ( CONSTRAINT "FK_T_MovieRequest4" FOREIGN KEY ("T_Movie_id") REFERENCES "S_0"."T_Movie" ("id"))
/
ALTER TABLE "S_0"."T_MovieRequest" ADD ( CONSTRAINT "FK_T_MovieRequest1" FOREIGN KEY ("barcode") REFERENCES "S_0"."T_Client" ("barcode"))
/
ALTER TABLE "S_0"."T_RentalRecord" ADD ( CONSTRAINT "FK_T_RentalRecord0" FOREIGN KEY ("barcode") REFERENCES "S_0"."T_Client" ("barcode"))
/
ALTER TABLE "S_0"."T_RentalRecord" ADD ( CONSTRAINT "FK_T_RentalRecord8" FOREIGN KEY ("T_SystemUser_id", "T_Worker_id") REFERENCES "S_0"."T_Worker" ("T_SystemUser_id", "id"))
/
ALTER TABLE "S_0"."T_RentalRecord" ADD ( CONSTRAINT "FK_T_RentalRecord7" FOREIGN KEY ("T_VideoMedium_barcode") REFERENCES "S_0"."T_VideoMedium" ("barcode"))
/
ALTER TABLE "S_0"."T_WarningMessageRecord" ADD ( CONSTRAINT "FK_T_WarningMessageRecord6" FOREIGN KEY ("barcode", "T_RentalRecord_id") REFERENCES "S_0"."T_RentalRecord" ("barcode", "id"))
/
COMMENT ON TABLE "S_0"."T_SystemUser" IS 'Пользователь системы. Например Администратор или Работник проката.
'
/
COMMENT ON TABLE "S_0"."T_RentalRecord" IS 'Запись о прокате'
/

