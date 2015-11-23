"""Manages the database. Each company will have a banner and text [file]
   that will be"""

import sqlite3
import crypto
import sys
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
	
def add_job(type, description, cid):
	conn = sqlite3.connect(DBNAME)
	c = conn.cursor()
	
	c.execute('SELECT job_type FROM {}'.format(JOBTNAME))

	ctnum = len(c.fetchall())
	
	
	c.execute("INSERT INTO {} values {}".format(JOBTNAME, JOBTPARAMS),
              (ctnum, type, description, cid))
	conn.commit()
	conn.close()
	
	
	return
def view_jobs():
	conn = sqlite3.connect(DBNAME)
	c = conn.cursor()

	c.execute('SELECT name, email, job_type, job_description FROM Companies, Job WHERE Companies.cid = Job.cid')
	
	rows = c.fetchall()
	print rows
	
	conn.commit()
	conn.close()
	return rows

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

def company_login(name, password):
    #check company's login information
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute('SELECT password FROM {} WHERE name = ?'.format(COMPANYTNAME),(name,))
    data = c.fetchone()
    if data is None:
        return False
    else:
        cipher = AES.new(SECRET)
        encoded = encodeAES(cipher, password)
        if data[0] == encoded:
            return True
        else:
            return False

def add_student(name, password):
    """creates unique id for each student, and adds student to the
       student table"""

    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    #get length    
    c.execute('SELECT name FROM {}'.format(STUDENTTNAME))

    ctnum = len(c.fetchall())

    #encrypt/encode text
    cipher = AES.new(SECRET)
    encoded = encodeAES(cipher, password)

    c.execute("INSERT INTO {} values {}".format(STUDENTNAME, STUDENTPARAMS),
              (name, encoded, ctnum))
    
    conn.commit()
    conn.close()

    return ctnum

def student_login(name, password):
    #check company's login information
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()

    c.execute('SELECT password FROM {} WHERE name = ?'.format(STUDENTTNAME),(name,))
    data = c.fetchone()
    if data is None:
        return False
    else:
        cipher = AES.new(SECRET)
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

