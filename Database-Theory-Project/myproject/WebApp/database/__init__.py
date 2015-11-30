"""Manages the database. Each company will have a banner and text [file]
   that will be"""

import sqlite3
import crypto
import sys
import time
sys.modules['crypto'] = crypto

from Crypto.Cipher import AES
import base64
import os

DBNAME = 'SICP.db' #Student Internship Connection Program
BLOCK_SIZE = 32 #block size for cipher object
PADDING = '{' #ensures encrypted value is multiple of block size
SECRET = '3\xe2^m\xadD\xfe\xd1E*T]Hh\x06\xf6\x91\x07t)\xe9VkX\xa9\x8e\xeb\x1ep\xe8+\xea'


#make a dateactive attribute to make sure companies log on
#update TRAITS and PARAMS to ensure things work
COMPANYTNAME = 'Companies'
COMPANYTRAITS = '(name text, password text, cid int primary key, active integer, email text)'
COMPANYPARAMS = '(?, ?, ?, ?, ?)'

STUDENTTNAME = 'Students'
STUDENTTRAITS = '(name text, password text, sid int primary key)'
STUDENTPARAMS = '(?, ?, ?)'

JOBTNAME = 'Job'
JOBTTRAITS = '(jobid int not null primary key autoincrement, job_type text not null, job_description text not null, cid int foreign key references Companies)'
JOBTPARAMS = '(?, ?, ?, ?)'
job_id_count = 0

def pad_text(s):
    """pads text to be encrypted"""
    return s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * PADDING

def encodeAES(c, pw):
    return base64.b64encode(c.encrypt(pad_text(pw)))

def create_db():
    """Creates the company and student tables.
       Deletes them if they already exist. Change the TRAIT constants
       to create new tables with different attributes"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    #create tables "Companies"
    c.execute('DROP TABLE IF EXISTS {}'.format(COMPANYTNAME))
    c.execute('DROP TABLE IF EXISTS {}'.format(STUDENTTNAME))
    
    c.execute('CREATE TABLE {} {}'.format(COMPANYTNAME, COMPANYTRAITS))
    c.execute('CREATE TABLE {} {}'.format(STUDENTTNAME, STUDENTTRAITS))

    conn.commit()
    conn.close()

    return
	
def add_job(type, description, email):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute ('SELECT cid FROM {} WHERE email = ?'.format(COMPANYTNAME), (email,))
    cid = c.fetchone()
    
    c.execute('SELECT job_type FROM {}'.format(JOBTNAME))

    ctnum = len(c.fetchall())


    c.execute("INSERT INTO {} values {}".format(JOBTNAME, JOBTPARAMS),
              (ctnum, type, description, cid[0]))
    conn.commit()
    conn.close()
	
def add_resume(filename, fsuid):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    # c.execute ('SELECT fsuid FROM {} WHERE name = ?'.format(STUDENTTNAME), (stuname,))
    # sid = c.fetchone()

    c.execute('SELECT resumeid FROM Resume')

    ctnum = len(c.fetchall())

    date = time.strftime("%x")
    


    c.execute("INSERT OR REPLACE INTO Resume values ((SELECT resumeid from Resume WHERE fsuid = ?), ?, ?, ?)", (fsuid, filename, fsuid, date))

    conn.commit()
    conn.close()
def view_students():
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute('SELECT name, Students.fsuid, filename, date FROM Students, Resume WHERE Students.fsuid = Resume.fsuid')

    
    rows = c.fetchall()
    print rows
    
    conn.commit()
    conn.close()
    return rows
def view_interested_students(email):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
    c.execute('SELECT cid FROM Companies WHERE email = ?', (email,))
    cid = c.fetchone()


    c.execute('SELECT Students.name, Students.fsuid, student_job_views.jid, Resume.filename FROM Students, student_job_views, Job, Companies, Resume WHERE Students.fsuid = student_job_views.sid AND student_job_views.jid = Job.jobid AND Resume.fsuid = Students.fsuid AND Job.cid = Companies.cid AND Companies.email = ?', (email,))
    
    rows = c.fetchall()
    print rows
    
    conn.commit()
    conn.close()
    return rows
def addInterest(jobid, email):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute('SELECT sviewid FROM student_job_views')

    ctnum = len(c.fetchall())
    c.execute('INSERT INTO student_job_views VALUES (?, ?, ?, ?)', (1, email, jobid, ctnum))

    conn.commit()
    conn.close()

def view_jobs():
	conn = sqlite3.connect(DBNAME)
	c = conn.cursor()

	c.execute('SELECT name, email, job_type, job_description, jobid FROM Companies, Job WHERE Companies.cid = Job.cid')
	
	rows = c.fetchall()
	print rows
	
	conn.commit()
	conn.close()
	return rows

def company_view_jobs(email):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
    #cid will equal session id passed in
    c.execute ('SELECT cid FROM Companies WHERE email = ?', (email,))
    cid = c.fetchone()
    c.execute('SELECT jobid, name, email, job_type, job_description FROM Companies, Job WHERE Companies.cid = ? AND Job.cid = ?', (cid[0], cid[0], ))
    
    rows = c.fetchall()
    
    
    conn.commit()
    conn.close()
    return rows
def addViewEmployer(filename, email):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute('SELECT cid FROM Companies Where email = ?', (email,))
    cid = c.fetchone()

    c.execute('SELECT resumeid from Resume where filename = ?', (filename,))
    rid = c.fetchone()

    c.execute('SELECT cviewid FROM comp_res_views')

    ctnum = len(c.fetchall())
    c.execute('INSERT INTO comp_res_views VALUES (?, ?, ?, ?)', (ctnum, 1, cid[0], rid[0]))

    conn.commit()
    conn.close()
def updateJob(email, jobid, type, description):
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute ('SELECT cid FROM Companies WHERE email = ?', (email,))
    cid = c.fetchone()

    c.execute('UPDATE JOB SET job_type = ?, job_description = ? WHERE jobid = ? AND cid = ?', (type, description, jobid, cid[0]))

    conn.commit()
    conn.close()

def add_company(name, password, email):
    """Creates unique id for each company, and adds company to the
       company table"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    #get length    
    c.execute('SELECT name FROM {}'.format(COMPANYTNAME))

    ctnum = len(c.fetchall())
    
    #encrypt/encode text
    cipher = AES.new(SECRET)
    encoded = encodeAES(cipher, password)

    c.execute("INSERT INTO {} values {}".format(COMPANYTNAME, COMPANYPARAMS),
              (name, encoded, ctnum, 1, email))
    
    conn.commit()
    conn.close()

    return ctnum

def company_login(email, password):
    #check company's login information
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
    cipher = AES.new(SECRET)


    c.execute('SELECT password FROM {} WHERE email = ?'.format(COMPANYTNAME),(email,))
    data = c.fetchone()
    if data is None:
        return False
    else:
        encoded = encodeAES(cipher, password)
        if data[0] == encoded:
            return True
        else:
            return False
def editJob(job_id):
	conn = sqlite3.connect(DBNAME)
	c = conn.cursor()

	c.execute("DELETE FROM Job WHERE jobid = "+job_id+"")
	print "removed"+job_id

	conn.commit()
	conn.close()


def add_student(name, password, email):
    """creates unique id for each student, and adds student to the
       student table"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
  

    #encrypt/encode text
    cipher = AES.new(SECRET)
    encoded = encodeAES(cipher, password)

    c.execute("INSERT INTO {} values {}".format(STUDENTTNAME, STUDENTPARAMS),
              (name, encoded, email))
    
    conn.commit()
    conn.close()


def student_login(email, password):
    #check company's login information
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
    cipher = AES.new(SECRET)

    c.execute('SELECT password FROM Students WHERE fsuid = ?',(email,))
    data = c.fetchone()
    if data is None:
        return False
    else:
        encoded = encodeAES(cipher, password)
        if data[0] == encoded:
            return True
        else:
            return False

#this is a generator function!
def view_company_t():
    """yields each company's info as a generator"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    for e in c.execute('SELECT * FROM {}'.format(COMPANYTNAME)):
        yield e
        
    conn.commit()
    conn.close()

#this is a generator function!
def view_student_t():
    """yields each student's info as a generator"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    DecodeAES = lambda c, e: c.decrypt(base64.b64decode(e)).rstrip(PADDING)

    for e in c.execute('SELECT * FROM {}'.format(STUDENTTNAME)):
        yield e

    conn.commit()
    conn.close()

