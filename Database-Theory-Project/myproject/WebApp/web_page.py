"""
    WISHLIST:
        IMMEDIATE:
            Upload files
        NOT:
            Change Current Students redirect
            Implement 'remember me' (not forgot your password?)
            Admin Account?
"""

import sqlite3
import database as adb

from flask import Flask, render_template, request, url_for, redirect, g, escape, session, send_from_directory
#from flask.ext.login import LoginManager, UserMixin, current_user, login_user, logout_user
#from werkzeug import generate_password_hash, check_password_hash

#init stuff
DATABASE = 'SCIP.db'
PORT = 5003
DEBUG = True
app = Flask(__name__)
app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'


#################################
#############WEBPAGE#############
#################################

@app.route('/')
def main():
    session.clear()
    app.logger.debug('Main page accessed')
    return render_template('index.html')

@app.route('/SCIP')
def choice():
    app.logger.debug('Main page accessed')
    
    return render_template('choice.html')

#
##
###Student pages
@app.route('/Students')
def student():
    return render_template('students.html')

@app.route('/Student/Login', methods=['GET', 'POST'])
def studentLogin():
    try:
        if escape(session['type']) == 'student':
            return redirect('/Student/Home')
    except:
        pass
    error = None
    if request.method == 'POST':
        if valid_login(request.form['email'],
                       request.form['password'],
                       True):
            session['username'] = request.form['email']
            session['type']  = "student"
            return redirect('/Student/Home')
        else:
            error = 'Invalid username/password'

    return render_template('studentlogin.html', error=error)
@app.route('/Student/Resume', methods=['GET', 'POST'])
def studentUpload():
    #how to add to resume table, add filename?
    if request.method == 'POST':
        f = request.files['resume']
        location = "static/resumes/"+session['username']+"_Resume.pdf"
        f.save(location)
        filename = session['username']+"_Resume.pdf"
        addresume(filename, session['username'])

    return render_template('studentResume.html')

def addresume(filename, stuname):
    adb.add_resume(filename, stuname)
@app.route('/Student/Register', methods=['GET', 'POST'])
def studentRegister():
    try:
        if escape(session['type']) == 'student':
            return redirect('/Student/Home')
    except:
        pass
    error = None
    if request.method == 'POST':
        #valid_login not implemented

        #returns 0 if successful, 1 if username already taken
        #2 if passwords dont match up, 3 if email already taken/invalid
        flag = reg_student(request.form['first'] + ' ' + request.form['last'],
                            request.form['password'],
                            request.form['cpassword'],
                            request.form['email'])
        if not flag: #log in not implemented
            session['username'] = request.form['email']
            session['type']  = 'student'
            return redirect('/Student/Home')
        elif flag == 1:
            error = 'Invalid username/password'
        elif flag == 2:
            error = 'Invalid e-mail'
        elif flag == 4:
            error = 'E-mail already in use!'

    return render_template('studentregister.html', error=error)


@app.route('/Student/Home')
def studentHome():
    return render_template('studenthome.html')

@app.route('/Student/Search', methods=['GET', 'POST'])
def studentSearch():
	table = []
	if request.method == 'POST':
		return render_template('studentsearch.html')
	else: 
		table = adb.view_jobs()
		print table
		return render_template('studentsearch.html', table=table)

@app.route('/Student/Apply')
def studentApply():
    return 'studentApply'
#
##
###Employee pages

@app.route('/Employers')
def employer():
    return render_template('employers.html')

@app.route('/Employers/Login', methods=['GET', 'POST'])
def employerLogin():
    try:
        if escape(session['type']) == 'employer':
            return redirect('/Employer/Home')
    except:
        pass    
    error = None
    if request.method == 'POST':
        #valid_login not implemented
        if valid_login(request.form['email'],
                       request.form['password'],
                       False):
            session['username'] = request.form['email'] 
            session['type'] = "employer"

            return redirect('/Employer/Home')
        
        else:
            error = 'Invalid username/password'        
        

    return render_template('employerlogin.html', error=error)
        
@app.route('/Employers/Register', methods=['GET', 'POST'])
def employerRegister():
    error = None
    if request.method == 'POST':
        #valid_login not implemented

        #returns 0 if successful, 1 if username already taken
        #2 if passwords dont match up, 3 if email already taken/invalid
        flag = reg_employer(request.form['username'],
                            request.form['password'],
                            request.form['cpassword'],
                            request.form['email'])
        if not flag: #log in not implemented
            session['username'] = request.form['username']
            session['type'] = 'employer'
            return redirect('/Employer/Home')
        elif flag == 1:
            error = 'Invalid username/password'
        elif flag == 2:
            error = 'Invalid e-mail'
        elif flag == 4:
            error = 'E-mail already in use!'

    return render_template('employerregister.html', error=error)

@app.route('/Employer/Home')
def employerHome():
    #user_id = request.cookies.get('YourSessionCookie')
     
    return render_template('employerhome.html')

@app.route('/Employer/Search')
def view_students():
    table = []
    if request.method == 'POST':
        return render_template('employersearch.html')
    else: 
        table = adb.view_students()
        return render_template('employersearch.html', table=table)


@app.route('/Employer/EditLogo')
def employerEditLogo():
    return 'employer'
	
@app.route('/Employer/InterestedStudents')
def showInterestedStduents():
    table = []
    if request.method == 'POST':
        return render_template('employersearch.html')
    else: 
        table = adb.view_interested_students(session['username'])
        return render_template('interestedstudents.html', table=table)
@app.route('/Employer/EditInternships', methods=['GET', 'POST'])
def employerEditInt():
    table = []
    print "ses: " + session['username']
    table = adb.company_view_jobs(session['username'])
    if request.method == 'POST':
        flag = editJob(request.form['job_id'])

    return render_template('editInternship.html', table=table)
@app.route('/Student/Search/<jobid>')
def showInterest(jobid):
    adb.addInterest(jobid, session['username'])
    return ('Interst shown in jobid: ' + jobid)
@app.route('/static/resumes/<path:filename>')
def addView(filename):
    print "HELLO"
    adb.addViewEmployer(filename, session['username'])
    return send_from_directory('static/resumes/', filename)


@app.route('/Employer/UpdateInternships', methods=['GET', 'POST'])
def empUpdateInt():
    table = []
    table = adb.company_view_jobs(session['username'])
    if request.method == 'POST':
        flag = updateJob(session['username'], request.form['job_id'], request.form['type'], request.form['description'])

    return render_template('updateInternships.html', table=table)
def updateJob(name, jobid, type, description):
    adb.updateJob(name, jobid, type, description)
@app.route('/Employer/AddInternships', methods=['GET', 'POST'])
def employerAddInt():
    error = None
    print session['username']
    if request.method == 'POST':
		#valid_login not implemented

		#returns 0 if successful, 1 if username already taken
		#2 if passwords dont match up, 3 if email already taken/invalid
		flag = addInt(request.form['type'],
							request.form['description'], session['username'])
		if not flag: #log in not implemented
			return log_employer_in('username')
		elif flag == 1:
			error = 'Invalid username/password'
		elif flag == 2:
			error = 'Invalid e-mail'
		elif flag == 3:
			error = 'Company already in use!'
    return render_template('AddInternships.html', error=error)
	
def addInt(type, description, cid):
	adb.add_job(type, description, cid)
	
def editJob(job_id):
	adb.editJob(job_id)


def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = connect_to_database()
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def valid_login(email, password, student = True):
    if student and adb.student_login(email, password):
        return True
    if not student and adb.company_login(email, password):
        return True

    return False

def log_employer_in(username):
    return redirect('/Employer/Home')

def log_student_in(username):
    return redirect('/Student/Home')

#need to check if email is a possible valid email
#need to have some checks on arguments
def reg_employer(name, password, cpassword, email):

    #return 1 if passwords not equal error
    if password != cpassword:
        return 1
    if '@' not in email:
        return 2
    for r in adb.view_company_t(): #companies can't have same name
        if name == r[0]:
            return 3
    
    else:
        adb.add_company(name, password, email)
        return False

    

def reg_student(name, password, cpassword, email):

    #return 1 if passwords not equal error
    if password != cpassword:
        return 1
    if '@' not in email:
        return 2
    for r in adb.view_company_t(): #students cant have same email
        if email == r[4]:
            return 4
    
    else:
        adb.add_student(name, password, email)


        return False

    
    
if __name__ == "__main__":
    app.logger.setLevel(0)
    app.run(port=PORT, debug=True)
