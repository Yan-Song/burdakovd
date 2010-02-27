from google.appengine.ext import webapp
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.api import urlfetch
import index

class Main(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/html'
    
    uid = self.request.get("uid")
    if uid:
        show_solved = self.request.get("show_solved")
        self.response.out.write(index.main(uid, show_solved))
    else:
        self.response.out.write(index.form())

application = webapp.WSGIApplication(
                                     [('/', Main)],
                                     debug=True)

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
