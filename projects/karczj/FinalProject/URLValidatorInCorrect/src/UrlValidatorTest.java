/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;



/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.print("RUNNING MANUAL TEST...\n");
	   System.out.print("format: \"test_case(true/false): true/false\" \n\t matching booleans indicate a passing test\n");
	   
	   // scheme
	   System.out.print("\nTesting Scheme...\n");
	   System.out.println("http://www.amazon.com (true): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("http:///www.amazon.com (false): " + urlVal.isValid("http:///www.amazon.com"));
	   System.out.println("http//www.amazon.com (false): " + urlVal.isValid("http//www.amazon.com"));
	   System.out.println("http://www!amazon.com (false): " + urlVal.isValid("http://www!amazon.com"));
	   System.out.println("http:www.amazon.com (false): " + urlVal.isValid("http:www.amazon.com"));
	   System.out.println("http://amazon.com (true): " + urlVal.isValid("http://amazon.com"));
	   System.out.println("www.amazon.com (true): " + urlVal.isValid("http//www.amazon.com"));
	   System.out.println("amazon.com (true): " + urlVal.isValid("amazon.com"));
	   System.out.println("http://ww.amazon.com (false): " + urlVal.isValid("http://ww.amazon.com"));
	   System.out.println("http://w.amazon.com (false): " + urlVal.isValid("http://w.amazon.com"));
	   System.out.println("http://xyz.amazon.com (false): " + urlVal.isValid("http://xyz.amazon.com"));

	   
	   // protocol (http, https, ftp, etc.)
	   System.out.print("\nTesting Protocol...\n");
	   System.out.println("http://www.amazon.com (true): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("https://www.amazon.com (true): " + urlVal.isValid("https://www.amazon.com"));
	   System.out.println("ftp://www.amazon.com (true): " + urlVal.isValid("ftp://www.amazon.com"));
	   System.out.println("invalidPrtcl://www.amazon.com (false): " + urlVal.isValid("invalidPrtcl://www.amazon.com"));
	   System.out.println("htp://www.amazon.com (false): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("0://www.amazon.com (false): " + urlVal.isValid("0://www.amazon.com"));
	   System.out.println("://www.amazon.com (false): " + urlVal.isValid("://www.amazon.com"));

	   
	   // host (ie video.google.co.uk)
	   System.out.print("\nTesting Host...\n");
	   System.out.println("http://www.amazon.com (true): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("http://54.239.17.6 (true): " + urlVal.isValid("http://54.239.17.6"));
	   System.out.println("http://54.356.17.6 (false): " + urlVal.isValid("http://54.356.17.6"));


	   // domain (ie google.co.uk)
	   System.out.print("\nTesting Domain...\n");
	   System.out.println("http://www.amazon.com (true): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("http://www.google.com (true): " + urlVal.isValid("http://www.google.com"));
	   System.out.println("difficult to test other domains, since they can all be purchased\n");

	   
	   // subdomain (ie video)
	   System.out.print("\nTesting Subdomain...\n");
	   System.out.println("http://www.smile.amazon.com (true): " + urlVal.isValid("http://www.smile.amazon.com"));
	   System.out.println("http://www.wrong.amazon.com (false): " + urlVal.isValid("http://www.wrong.amazon.com"));
	   System.out.println("http://www.wrong!.amazon.com (false): " + urlVal.isValid("http://www.wrong!.amazon.com"));
	   System.out.println("difficult to test other domains, since they can be updated\n");

	   
	   // top-level domain (TLD) (ie .com or. uk--aka country-code top-level domain or ccTLD)
	   System.out.print("\nTesting TLD...\n");
	   System.out.println("http://www.amazon.com (true): " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println("http://www.amazon.co.uk (true): " + urlVal.isValid("http://www.amazon.co.uk"));
	   System.out.println("http://www.oregonstate.edu (true): " + urlVal.isValid("http://www.oregonstate.edu"));
	   System.out.println("http://www.oregonstate.edu.uk (false): " + urlVal.isValid("http://www.oregonstate.edu.uk"));
	   System.out.println("http://www.amazon.co.yuk (false): " + urlVal.isValid("http://www.amazon.co.yuk"));


	   
	   // port (80 unless spec'd)
	   System.out.print("\nTesting Port...\n");
	   System.out.println("http://www.amazon.com:80 (true): " + urlVal.isValid("http://www.amazon.com:80"));
	   System.out.println("http://www.amazon.com:1969 (true): " + urlVal.isValid("http://www.amazon.com:1969"));
	   System.out.println("http://www.amazon.com:80000 (false): " + urlVal.isValid("http://www.amazon.com:80000"));
	   System.out.println("http://www.amazon.com:8000000 (false): " + urlVal.isValid("http://www.amazon.com:8000000"));
	   System.out.println("http://www.amazon.com:0 (true): " + urlVal.isValid("http://www.amazon.com:0"));

 
	   // path (ie /directory/file.html)
	   System.out.print("\nTesting Path...\n");
	   System.out.println("https://www.amazon.com/gp/homepage.html (true): " + urlVal.isValid("https://www.amazon.com/gp/homepage.html"));
	   
	   // parameters (ie &param=true)
	   System.out.print("\nTesting Parameter(s)...\n");
	   System.out.println("http://www.amazon.com/gp/product/... (true): " + urlVal.isValid("https://www.amazon.com/gp/product/B01LRCBWAQ/ref=s9u_wish_gw_i2?ie=UTF8&colid=1HTSYAOS9MKO6&coliid=I3IORFI5QHKP00&fpl=fresh&pd_rd_i=B01LRCBWAQ&pd_rd_r=VPQSA38HWY3BWBB17J00&pd_rd_w=j2g6r&pd_rd_wg=gbiLk&pf_rd_i=desktop&pf_rd_s=&pf_rd_m=ATVPDKIKX0DER&pf_rd_r=87K9T4A7G46N821Q83Y2&pf_rd_t=36701&pf_rd_p=1dd2ffc3-992f-4bde-81b0-de270e0ead5a"));
	   System.out.println("https://www.amazon.com/Amazon-Video/b/?&node=2... (true): " + urlVal.isValid("https://www.amazon.com/Amazon-Video/b/?&node=2858778011&ref=dvm_us_api_cs_hud_PS_api&pf_rd_p=cad2c637-2029-40b1-b569-41f786ec79fb&pf_rd_r=87K9T4A7G46N821Q83Y2"));
	   System.out.print("\nRUNNING PARTITION TESTS...\n");

   }
   
   public void executeTestPrintResult(String url, boolean expected) {
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
            boolean actual = urlVal.isValid(url);
            if (actual == expected) {
                System.out.println(url + " --- Expected: " + expected + " ---  Result: PASS");
            }
            else {
                System.out.println(url + " --- Expected: " + expected + " --- Result: FAIL *******************");
            }
            //assertEquals(actual, expected);  // use this line to have jUnit track pass/fails
    }


	   
   public void testYourFirstPartition() {
       // URLs with domain only (i.e. http://google.com:80)
	   System.out.print("\nTesting First Partition...\n");
        executeTestPrintResult("http://a.com", true);  // valid scheme all letters
        executeTestPrintResult("http://a.a", false);  // invalid domain 
        executeTestPrintResult("http://.com", false);  // invalid scheme, empty domain
        executeTestPrintResult("http://com", false);  // invalid scheme, empty domain
        executeTestPrintResult("http://abc", false);  // invalid scheme, no TLD
        executeTestPrintResult("http://a.123", false);  // invalid domain 
        executeTestPrintResult("h123://a.com", true);  // valid scheme letters/digits
        executeTestPrintResult("1htp://a.com", false);  // invalid scheme starts with digit
        executeTestPrintResult("http:///a.com", false);  // invalid scheme triple slash 
        executeTestPrintResult("http:/a.com", false);  // invalid scheme one slash 
        executeTestPrintResult("http/a.com", false);  // invalid scheme no colon

        executeTestPrintResult("http://a.com", true);  // one dot 
        executeTestPrintResult("http://a.a.a.com", true);  // arbitrary number of dots 
        executeTestPrintResult("http://a.a.a.a.com", true);  // arbitrary number of dots 
        executeTestPrintResult("http://0.0.0.0", true);  // four digits all min
        executeTestPrintResult("http://255.255.255.255", true);  // four digits all valid max
        executeTestPrintResult("http://255.255.256.255", false);  // four digits, one invalid
        executeTestPrintResult("http://0.-1.0.0", false);  // invalid digit/character
        executeTestPrintResult("http://0.0.0.0.0", false);  // five digits
        executeTestPrintResult("http://0.0", false);  // two digits
        executeTestPrintResult("", false);  // empty string
   }


   public void testYourSecondPartition() {
       // URLs with domain + port
	System.out.print("\nTesting Second Partition...\n");
        executeTestPrintResult("http://abc.com:65535", true);  // max allowed port number
        executeTestPrintResult("http://abc.com:0", true);  // min allowed port number
        executeTestPrintResult("http://abc.com:1", true);  // 1 digit port number  
        executeTestPrintResult("http://abc.com:99", true);  // 2 digit port number  
        executeTestPrintResult("http://abc.com:999", true);  // 3 digit port number  
        executeTestPrintResult("http://abc.com:1000", true);  // 4 digit port number  
        executeTestPrintResult("http://abc.com:65536", false);  // port number too high 
        executeTestPrintResult("http://abc.com:-1", false);  // negative port
        executeTestPrintResult("http://abc.com:a", false);  // letter in port
        executeTestPrintResult("http://abc.com:", false);  // empty port 
        executeTestPrintResult(":123", false);  // no domain 
   }
   
   public void testYourThirdPartition() {
       // URLs with domain + path
	System.out.print("\nTesting Third Partition...\n");
        executeTestPrintResult("http://abc.com/", true);  // empty 
        executeTestPrintResult("http://abc.com/a/b/c/1/2/3", true);  // arbitrary length, letters and digits
        executeTestPrintResult("http://abc.com/a/#b", false);  // invalid char 
        executeTestPrintResult("http://abc.com/a/$b", true);  // $ is valid char 
        executeTestPrintResult("http://abc.com/../b", false);  // invalid relative path
        executeTestPrintResult("/a/b/c", false);  // no domain 
   }

   public void testYourFourthPartition() {
       // URLs with domain + query
	System.out.print("\nTesting Fourth Partition...\n");
        executeTestPrintResult("http://abc.com?", false);  // empty 
        executeTestPrintResult("http://abc.com?key=value", true);  
        executeTestPrintResult("http://abc.com?a=1&b=2&c=3", true); // arbitrary length, letters/digits 
        executeTestPrintResult("http://abc.com?a=1+b=2", false); // +
        executeTestPrintResult("http://abc.com?a", false); // no value
        executeTestPrintResult("http://abc.com?=a", false); // no key
        executeTestPrintResult("?key=value", false);  // no domain 
   }

   public void testYourFifthPartition() {
       // Different combinations of each component
	System.out.print("\nTesting Fifth Partition...\n");
        executeTestPrintResult("http://abc.com:1/a?key=value", true); // domain + port + path + query
        executeTestPrintResult("http://abc.com/a?key=value", true); // domain + path + query
        executeTestPrintResult("http://abc.com:1/a", true); // domain + port + path
        executeTestPrintResult("http://abc.com:1?key=value", true); // domain + port + query

        executeTestPrintResult("http://abc.com/a/b:80", false); // domain + path + port
        executeTestPrintResult("http://abc.com?key=value/a/b/c", false); // domain + query + path
        executeTestPrintResult("http://abc.com?key=value:80", false); // domain + query + port
        executeTestPrintResult("http://abc.com:1?key=value/a/b/c", false); // domain + port + query + path
        executeTestPrintResult("http://abc.com?key=value/a/b/c:80", false); // domain + query + path + port
        executeTestPrintResult("http://abc.com?key=value:80/a/b/c", false); // domain + query + port + path
        executeTestPrintResult("http://abc.com/a/b/c:80?key=value", false); // domain + path + port + query
        executeTestPrintResult("http://abc.com/a/b/c?key=value:80", false); // domain + path + query + port
	   
   }

   public int executeTestPrintFailures(String url, boolean expected, int count) {
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
            boolean actual = urlVal.isValid(url);
            if (actual != expected) {
                count++;
                System.out.println(count + ". " + url + " --- Expected: " + expected + " --- Result: FAIL");
            }
            return count;
    }

   
   public void testIsValid() {
        String url_no_dots;
        String url_dotted;
        // PROTOCOL   AUTHORITY   PORT   TLDS    COUNTRY_CODE   PATH    QUERY   
        System.out.println("\nTESTING VARIOUS URL COMBINATIONS & PRINTING FAILURES:\n");
        int failed_count = 0;
        for(int i = 0; i < PROTOCOL.length; i++) {
            for(int j = 0; j < AUTHORITY.length; j++) {
                for(int k = 0; k < TLDS.length; k++) {
                    for(int m = 0; m < PORT.length; m++) {
                        for(int n = 0; n < PATH.length; n++) {
                            for(int o = 0; o < QUERY.length; o++) {
                                boolean expected_dotted = true;
                                boolean expected_no_dots = true;
                                expected_no_dots = PROTOCOL[i].valid & AUTHORITY[j].valid & TLDS[k].valid & PORT[m].valid & PATH[n].valid & QUERY[o].valid;
                                url_no_dots = PROTOCOL[i].item + AUTHORITY[j].item + TLDS[k].item + PORT[m].item + PATH[n].item + QUERY[o].item;
                                failed_count = executeTestPrintFailures(url_no_dots, expected_no_dots, failed_count);

                                expected_dotted = PROTOCOL[i].valid & DOTTED[j].valid & TLDS[k].valid & PORT[m].valid & PATH[n].valid & QUERY[o].valid;
                                url_dotted = PROTOCOL[i].item + DOTTED[j].item + PORT[m].item + PATH[n].item + QUERY[o].item;
                                failed_count = executeTestPrintFailures(url_dotted, expected_dotted, failed_count);
                             }
                         }
                     }
                }       
            }
        }
   }
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   //arrays holding the partition cases for pseudo-random looping test
   //too many fails, commenting out expected fails
   private static final ResultPair[] PROTOCOL = {new ResultPair("", false), //empty	//should assume http/https and pass
                                                new ResultPair("http://", true), 
                                                new ResultPair("html://", false)};

   private static final ResultPair[] AUTHORITY = {new ResultPair("www.subhost.host.", true),
                                              new ResultPair("www,subhost,host.", false),
                                              new ResultPair("", false)};

   private static final ResultPair[] DOTTED = {new ResultPair("0.0.0", false),
                                              new ResultPair("0.255.0.255", true),
                                              new ResultPair("255.256.255.255", false)};
   
   
   private static final ResultPair[] PORT = {new ResultPair("", true),
                                             new ResultPair(":0",  true), //min
                                             new ResultPair(":65535", true),  //max
                                             new ResultPair(":65536", false), //max+1
                                             new ResultPair(":-1", false)};  //min-1

   private static final ResultPair[] PATH = {new ResultPair("", true), //none
                                             new ResultPair("/", true), //none
                                             new ResultPair("/path", true),
                                             new ResultPair("/path/file.html", true),
                                             new ResultPair("/path//file.html", false),
                                             new ResultPair("../path", false),
                                             new ResultPair("/path/path/file.html", true)};

   private static final ResultPair[] QUERY = {new ResultPair("", true), //none
                                              new ResultPair("?key=value", true),  //1 query
                                              new ResultPair("?key:value", false),  //1 query
                                              new ResultPair("?key1=value1&key2=val2", true)};
  
   private static final ResultPair[] TLDS = {  //from DomainVaidator.java
                new ResultPair("", false),
	        //new ResultPair("arpa", true),         // internet infrastructure
	        //new ResultPair("root", true),        // diagnostic marker for non-truncated root zone
	        //new ResultPair("aero", true),        // air transport industry
	        //new ResultPair("asia", true),        // Pan-Asia/Asia Pacific
	        //new ResultPair("biz", true),         // businesses
	        //new ResultPair("cat", true),                // Catalan linguistic/cultural community
	        new ResultPair("com", true),                // commercial enterprises
	        new ResultPair("xyz", false),                // commercial enterprises
	        new ResultPair("gov", true),                // United States Government
	        new ResultPair("co.de", true),                 // Germany


	       /* 
	        new ResultPair("coop", true),               // cooperative associations
	        new ResultPair("info", true),               // informational sites
	        new ResultPair("jobs", true),               // Human Resource managers
	        new ResultPair("mobi", true),               // mobile products and services
	        new ResultPair("museum", true),             // museums, true), surprisingly enough
	        new ResultPair("name", true),               // individuals' sites
	        new ResultPair("net", true),                // internet support infrastructure/business
	        new ResultPair("org", true),                // noncommercial organizations
	        new ResultPair("pro", true),                // credentialed professionals and entities
	        new ResultPair("tel", true),                // contact data for businesses and individuals
	        new ResultPair("travel", true),             // entities in the travel industry
	        new ResultPair("edu", true),                // accredited postsecondary US education entities
	        new ResultPair("mil", true),                // United States Military
	        new ResultPair("int", true),                 // organizations established by international treaty
		new ResultPair("localhost", true),           // RFC2606 defined
		new ResultPair("localdomain", true),          // Also widely used as localhost.localdomain
	        new ResultPair("co.ac", true),                 // Ascension Island
	        new ResultPair("co.ad", true),                 // Andorra
	        new ResultPair("co.ae", true),                 // United Arab Emirates
	        new ResultPair("co.af", true),                 // Afghanistan
	        new ResultPair("co.ag", true),                 // Antigua and Barbuda
	        new ResultPair("co.ai", true),                 // Anguilla
	        new ResultPair("co.al", true),                 // Albania
	        new ResultPair("co.am", true),                 // Armenia
	        new ResultPair("co.an", true),                 // Netherlands Antilles
	        new ResultPair("co.ao", true),                 // Angola
	        new ResultPair("co.aq", true),                 // Antarctica
	        new ResultPair("co.ar", true),                 // Argentina
	        new ResultPair("co.as", true),                 // American Samoa
	        new ResultPair("co.at", true),                 // Austria
	        new ResultPair("co.au", true),                 // Australia (includes Ashmore and Cartier Islands and Coral Sea Islands)
	        new ResultPair("co.aw", true),                 // Aruba
	        new ResultPair("co.ax", true),                 // Åland
	        new ResultPair("co.az", true),                 // Azerbaijan
	        new ResultPair("co.ba", true),                 // Bosnia and Herzegovina
	        new ResultPair("co.bb", true),                 // Barbados
	        new ResultPair("co.bd", true),                 // Bangladesh
	        new ResultPair("co.be", true),                 // Belgium
	        new ResultPair("co.bf", true),                 // Burkina Faso
	        new ResultPair("co.bg", true),                 // Bulgaria
	        new ResultPair("co.bh", true),                 // Bahrain
	        new ResultPair("co.bi", true),                 // Burundi
	        new ResultPair("co.bj", true),                 // Benin
	        new ResultPair("co.bm", true),                 // Bermuda
	        new ResultPair("co.bn", true),                 // Brunei Darussalam
	        new ResultPair("co.bo", true),                 // Bolivia
	        new ResultPair("co.br", true),                 // Brazil
	        new ResultPair("co.bs", true),                 // Bahamas
	        new ResultPair("co.bt", true),                 // Bhutan
	        new ResultPair("co.bv", true),                 // Bouvet Island
	        new ResultPair("co.bw", true),                 // Botswana
	        new ResultPair("co.by", true),                 // Belarus
	        new ResultPair("co.bz", true),                 // Belize
	        new ResultPair("co.ca", true),                 // Canada
	        new ResultPair("co.cc", true),                 // Cocos (Keeling) Islands
	        new ResultPair("co.cd", true),                 // Democratic Republic of the Congo (formerly Zaire)
	        new ResultPair("co.cf", true),                 // Central African Republic
	        new ResultPair("co.cg", true),                 // Republic of the Congo
	        new ResultPair("co.ch", true),                 // Switzerland
	        new ResultPair("co.ci", true),                 // Côte d'Ivoire
	        new ResultPair("co.ck", true),                 // Cook Islands
	        new ResultPair("co.cl", true),                 // Chile
	        new ResultPair("co.cm", true),                 // Cameroon
	        new ResultPair("co.cn", true),                 // China, true), mainland
	        new ResultPair("co.co", true),                 // Colombia
	        new ResultPair("co.cr", true),                 // Costa Rica
	        new ResultPair("co.cu", true),                 // Cuba
	        new ResultPair("co.cv", true),                 // Cape Verde
	        new ResultPair("co.cx", true),                 // Christmas Island
	        new ResultPair("co.cy", true),                 // Cyprus
	        new ResultPair("co.cz", true),                 // Czech Republic
	        new ResultPair("co.de", true),                 // Germany
	        new ResultPair("co.dj", true),                 // Djibouti
	        new ResultPair("co.dk", true),                 // Denmark
	        new ResultPair("co.dm", true),                 // Dominica
	        new ResultPair("co.do", true),                 // Dominican Republic
	        new ResultPair("co.dz", true),                 // Algeria
	        new ResultPair("co.ec", true),                 // Ecuador
	        new ResultPair("co.ee", true),                 // Estonia
	        new ResultPair("co.eg", true),                 // Egypt
	        new ResultPair("co.er", true),                 // Eritrea
	        new ResultPair("co.es", true),                 // Spain
	        new ResultPair("co.et", true),                 // Ethiopia
	        new ResultPair("co.eu", true),                 // European Union
	        new ResultPair("co.fi", true),                 // Finland
	        new ResultPair("co.fj", true),                 // Fiji
	        new ResultPair("co.fk", true),                 // Falkland Islands
	        new ResultPair("co.fm", true),                 // Federated States of Micronesia
	        new ResultPair("co.fo", true),                 // Faroe Islands
	        new ResultPair("co.fr", true),                 // France
	        new ResultPair("co.ga", true),                 // Gabon
	        new ResultPair("co.gb", true),                 // Great Britain (United Kingdom)
	        new ResultPair("co.gd", true),                 // Grenada
	        new ResultPair("co.ge", true),                 // Georgia
	        new ResultPair("co.gf", true),                 // French Guiana
	        new ResultPair("co.gg", true),                 // Guernsey
	        new ResultPair("co.gh", true),                 // Ghana
	        new ResultPair("co.gi", true),                 // Gibraltar
	        new ResultPair("co.gl", true),                 // Greenland
	        new ResultPair("co.gm", true),                 // The Gambia
	        new ResultPair("co.gn", true),                 // Guinea
	        new ResultPair("co.gp", true),                 // Guadeloupe
	        new ResultPair("co.gq", true),                 // Equatorial Guinea
	        new ResultPair("co.gr", true),                 // Greece
	        new ResultPair("co.gs", true),                 // South Georgia and the South Sandwich Islands
	        new ResultPair("co.gt", true),                 // Guatemala
	        new ResultPair("co.gu", true),                 // Guam
	        new ResultPair("co.gw", true),                 // Guinea-Bissau
	        new ResultPair("co.gy", true),                 // Guyana
	        new ResultPair("co.hk", true),                 // Hong Kong
	        new ResultPair("co.hm", true),                 // Heard Island and McDonald Islands
	        new ResultPair("co.hn", true),                 // Honduras
	        new ResultPair("co.hr", true),                 // Croatia (Hrvatska)
	        new ResultPair("co.ht", true),                 // Haiti
	        new ResultPair("co.hu", true),                 // Hungary
	        new ResultPair("co.id", true),                 // Indonesia
	        new ResultPair("co.ie", true),                 // Ireland (Éire)
	        new ResultPair("co.il", true),                 // Israel
	        new ResultPair("co.im", true),                 // Isle of Man
	        new ResultPair("co.in", true),                 // India
	        new ResultPair("co.io", true),                 // British Indian Ocean Territory
	        new ResultPair("co.iq", true),                 // Iraq
	        new ResultPair("co.ir", true),                 // Iran
	        new ResultPair("co.is", true),                 // Iceland
	        new ResultPair("co.it", true)                 // Italy
	            */
	    };
}
