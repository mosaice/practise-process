require 'rest-client'
require 'json'

threads = []

source = {
  studentId: ['716901010002', '716901010067'],
  course: {
    mao: {
      resourceId: '243198',
      id: '1767'
    },
    english: {
      resourceId: '250651',
      id: '2064',
    },
    sql: {
      resourceId: '250041',
      id: '2323',
    },
    ds: {
      resourceId: '251030',
      id: '2484',
    },
    java: {
      resourceId: '251035',
      id: '2469',
    }
  }
}

header = {
  :cookies => {'ASPSESSIONIDCQABBASA' => 'KAAFLFCCDHNIOAGKIAAMJCCD'},
  :content_type=>"application/json; charset=utf-8"
}

base_url = 'http://www.onlinesjtu.com/SCEPlayer/Default.aspx'

source[:course].values.each do |course|
  getParams = {
    'studentid': source[:studentId][0],
    'courseid': course[:id],
    'termidentify': '2017_3'
  }

  page = RestClient.get(base_url, params: getParams)
  resourceReg = /id="list-item-(\d+)"\sclass="status-no"/

  source[:studentId].each do |student|
    threads << Thread.new do
      page.body.scan(resourceReg) do |resArr|
        payload =  { 'resourceId': resArr[0], 'studentId': student }
        RestClient.post(
          "#{base_url}/AddDacLog",
          payload.to_json,
          header
        ) do |res, req, result|
          p "#{payload.to_s} #{res.code} #{result.body}"
        end
      end
    end
  end
end

threads.each {|t| t.join}

