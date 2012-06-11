#! /usr/bin/env python

import optparse, getpass
import urllib, urllib2
import base64
import itertools, mimetools, mimetypes
import platform
from datetime import datetime
import os, sys
import re

#===============================================================
#
#   The MultiPartForm class was borrowed from Doug Hellmann
#   http://broadcast.oreilly.com/2009/07/pymotw-urllib2.html 
#   doug.hellmann@gmail.com
#   https://twitter.com/doughellmann
#
#===============================================================
class MultiPartForm(object):
    """Accumulate the data to be used when posting a form."""
    
    def __init__(self):
        self.form_fields = []
        self.files = []
        self.boundary = mimetools.choose_boundary()
        return

    def get_content_type(self):
        return 'multipart/form-data; boundary=%s' % self.boundary

    def add_field(self, name, value):
        """Add a simple field to the form data."""
        self.form_fields.append((name, value))
        return

    def add_file(self, fieldname, filename, fileHandle, mimetype=None):
        """Add a file to be uploaded."""
        body = fileHandle.read()
        if mimetype is None:
            mimetype = mimetypes.guess_type(filename)[0] or 'application/octet-stream'
        self.files.append((fieldname, filename, mimetype, body))
        return

    def __str__(self):
        """Return a string representing the form data, including attached files."""
        # Build a list of lists, each containing "lines" of the
        # request. Each part is separated by a boundary string.
        # Once the list is built, return a string where each
        # line is separated by '\r\n'.
        parts = []
        part_boundary = '--' + self.boundary
        
        # Add the form fields
        parts.extend(
            [ part_boundary,
              'Content-Disposition: form-data; name="%s"' % name,
              '',
              value,
              ]
            for name, value in self.form_fields
            )
        
        # Add the files to upload
        parts.extend(
            [ part_boundary,
              'Content-Disposition: file; name="%s"; filename="%s"' % \
            (field_name, filename),
              'Content-Type: %s' % content_type,
              '',
              body,
              ]
            for field_name, filename, content_type, body in self.files
            )
        
        # Flatten the list and add closing boundary marker,
        # then return CR+LF separated data
        flattened = list(itertools.chain(*parts))
        flattened.append('--' + self.boundary + '--')
        flattened.append('')
        return '\r\n'.join(flattened)

#===============================================================
#
#  End of class MultiPartForm(object)
#
#===============================================================
if __name__ == "__main__":

    # Setup options parser
    parser = optparse.OptionParser(
        usage = "usage: %prog [options] file1 [file2 file3 ...]"+
        "\nCall with --help for more info.",
        description = "Post plots to specified e-log."
        )

    parser.add_option("--nd", action="store_const", const="nd", dest="elog",
                      help="Post to the Notre Dame e-log")

    parser.add_option("--shyft", action="store_const", const="shyft", dest="elog",
                      help="Post to the JHU SHyFT e-log")

    parser.add_option("--demo", action="store_const", const="demo", dest="elog",
                      help="Post to the demo logbook running locally")

    parser.add_option("-d","--debug", action="store", type="int", dest="debug",
                      help="Set to >= 1 for debug output.", default=0)

    parser.set_defaults(elog="nd")
    
    options, args = parser.parse_args()

    if len(args) == 0:
        parser.print_usage()
        sys.exit(2)

    #We may need the username and password in configuring some things
    username = raw_input("Username: ")
    password = getpass.getpass("Password: ")

    #We should also start setting up the multipart form data, since
    #some of it is e-log dependent
    print "Preparing e-log post for elog " + options.elog
    form = MultiPartForm()
    form.add_field('cmd', 'Submit')
    form.add_field('unm',username)
    form.add_field('upwd',base64.b64encode(password))
    form.add_field('encoding','plain')
    entry = ("These plots were automatically posted by postPlots.py on " +
             datetime.now().strftime("%A, %b %d, %Y %I:%M%p") +
             " from " + platform.node() +
             " (Python " + platform.python_version()+")")
    form.add_field('Text',entry)

    if options.elog == "nd":
        print "Adding ND specific post data."
        form.add_field('subject','Automatic plots posting')
        form.add_field('category','Auto')
        elogUrl = "http://www.hep.nd.edu/elog/" + username + "/"
        #elogUrl = "http://localhost:8080/"
        #Configure url handling for authentication and cookies, for login
        passMan = urllib2.HTTPPasswordMgrWithDefaultRealm()
        passMan.add_password(None,'http://www.hep.nd.edu', '', 'ndhep' )


        #Default opener, used for the password request
        opener1 = urllib2.build_opener(urllib2.HTTPBasicAuthHandler(passMan),
                                      urllib2.HTTPCookieProcessor(),
                                      urllib2.HTTPHandler(debuglevel=options.debug))


        #No-redirect opener: Why am I building the opener in this
        #strange way, instead of using the code above?  Because in
        #older versions of Python, redirects after a POST are not
        #handled correctly.  ELOG responds to a successful post with a
        #redirect, which then hangs.  Since we don't actually care
        #about the redirection, I build an opener that doesn't include
        #redirection (or a bunch of other default things).  Should
        #work fine-- ignores request to redirect and terminates.
        opener2 = urllib2.OpenerDirector()
        opener2.add_handler(urllib2.HTTPHandler(debuglevel=options.debug))
        opener2.add_handler(urllib2.ProxyHandler())
        opener2.add_handler(urllib2.HTTPBasicAuthHandler(passMan))
        opener2.add_handler(urllib2.HTTPCookieProcessor())
        opener2.add_handler(urllib2.HTTPDefaultErrorHandler())
        opener2.add_handler(urllib2.HTTPErrorProcessor())

    elif options.elog == "shyft":
        print "Adding SHyFT (JHU) specific post data."
        #form.add_field('exp','top')
        form.add_field('Type','Progress')
        form.add_field('Category','SHyFT')
        form.add_field('Subject','Automatic plots posting')
        elogUrl = "http://hep.pha.jhu.edu:8080/top/"

        #No authentication here, just cookies for login
        opener1 = urllib2.build_opener(urllib2.HTTPCookieProcessor())

        #No-redirect opener: Why am I building the opener in this
        #strange way, instead of using the code above?  Because in
        #older versions of Python, redirects after a POST are not
        #handled correctly.  ELOG responds to a successful post with a
        #redirect, which then hangs.  Since we don't actually care
        #about the redirection, I build an opener that doesn't include
        #redirection (or a bunch of other default things).  Should
        #work fine-- ignores request to redirect and terminates.
        opener2 = urllib2.OpenerDirector()
        opener2.add_handler(urllib2.HTTPHandler(debuglevel=options.debug))
        opener2.add_handler(urllib2.ProxyHandler())
        opener2.add_handler(urllib2.HTTPCookieProcessor())
        opener2.add_handler(urllib2.HTTPDefaultErrorHandler())
        opener2.add_handler(urllib2.HTTPErrorProcessor())

    elif options.elog == "demo":
        print "Adding to local demo logbook"
        form.add_field('author','me')
        form.add_field('type','Other')
        elogUrl = "http://localhost:8080/demo"

        #No authentication here, just cookies for login
        opener1 = urllib2.build_opener(urllib2.HTTPCookieProcessor())

        #No-redirect opener: Why am I building the opener in this
        #strange way, instead of using the code above?  Because in
        #older versions of Python, redirects after a POST are not
        #handled correctly.  ELOG responds to a successful post with a
        #redirect, which then hangs.  Since we don't actually care
        #about the redirection, I build an opener that doesn't include
        #redirection (or a bunch of other default things).  Should
        #work fine-- ignores request to redirect and terminates.
        opener2 = urllib2.OpenerDirector()
        opener2.add_handler(urllib2.HTTPHandler(debuglevel=options.debug))
        opener2.add_handler(urllib2.ProxyHandler())
        opener2.add_handler(urllib2.HTTPCookieProcessor())
        opener2.add_handler(urllib2.HTTPDefaultErrorHandler())
        opener2.add_handler(urllib2.HTTPErrorProcessor())

    else :
        print ("ERROR:  Don't know anything about elog destination type " +
               options.elog +".  Aborting!")
        sys.exit(255)
    
    #Now, add each of the files on the argument list
    print "Attaching files..."
    fileNum = 0
    for fileName in args :
        if not os.path.exists(fileName) :
            print ("ERROR: Cannot find file " + fileName + ".  Aborting!")
            sys.exit(255)

        print "Attaching file " + fileName
        form.add_file(("attfile%d" % fileNum), fileName, 
                  fileHandle=open(fileName,'r'))
        fileNum += 1
    

    #Log in to the e-log to get the necessary cookie set for posting
    params = urllib.urlencode({'uname':username, 'upassword':password})
    req = urllib2.Request(elogUrl+'?'+params)
    try:
        f = opener1.open(req)
    except IOError, e:
        print 'Error trying to log in to elog.'
        if hasattr(e, 'reason'):
            print 'We failed to reach a server.'
            print 'Reason: ', e.reason
            sys.exit(255)
        elif hasattr(e, 'code'):
            print 'The server couldn\'t fulfill the request.'
            print 'Error code: ', e.code
            print e.headers
            sys.exit(255)
        else :
            print 'Unknown error'
            sys.exit(255)

    page = f.read()

    #Some e-logs like to see who the author of the post is
    p = re.compile(r'Logged in as "([\w\s]+)"')
    m = p.search(page)
    if m :
        author =  m.group(1)
        if options.elog == "shyft":
            form.add_field('Author',author)
    else:
        print "Error logging in.  Please try again."
        sys.exit(2)
        

##    print "==========================="
##    print page
##    print "==========================="

    #Now, try to send the form
    req = urllib2.Request(elogUrl)
    req.add_header('User-agent', 'ELOG')
    req.add_header('Content-type', form.get_content_type())
    body = str(form)
    req.add_header('Content-length', len(body))
    req.add_data(body)

##    print "URL"
##    print req.get_full_url()
##    print "SELECTOR"
##    print req.get_selector()
##    print "DATA"
##    print req.get_data()
    
    try:
        f = opener2.open(req)
    except IOError, e:
        if hasattr(e, 'reason'):
            print 'Error trying to post to e-log'
            print 'We failed to reach a server.'
            print 'Reason: ', e.reason
            sys.exit(255)
        elif hasattr(e, 'code'):
            #Only complain if it's not a redirection attempt
            if e.code != 301 and e.code != 302:
                print 'Error trying to post to e-log'
                print 'The server couldn\'t fulfill the request.'
                print 'Error code: ', e.code
                print e.headers
                sys.exit(255)
        else :
            print 'Error trying to post to e-log'
            print 'Unknown error'
            sys.exit(255)


##    print "==========================="
##    print f.read()
##    print "==========================="

    print "Done!"
        


