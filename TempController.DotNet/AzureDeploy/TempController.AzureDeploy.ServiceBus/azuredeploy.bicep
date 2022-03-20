@allowed([
  'dev'
  'tst'
  'prd'
])
@description('The deployment environment')
param env string

@description('The location of the resource deployment')
param location string = resourceGroup().location

// Mapping of the deployment location to its abbreviation
var locationToAbbr = {
  centralus: 'cus'
  eastus: 'eus'
  westus: 'eus'
}

var locationAbbr = locationToAbbr[location]

var serviceBusName = 'svbs-tempcontroller-${locationAbbr}-${env}'

resource serviceBus 'Microsoft.ServiceBus/namespaces@2021-11-01' = {
  name: serviceBusName
  location: location
  sku: {
    name: 'Basic'
    tier: 'Basic'
  }

  resource queueToDevice 'queues@2017-04-01' = {
    name: 'tempcontroller-sender'
    properties: {
      defaultMessageTimeToLive: 'PT5M'
      deadLetteringOnMessageExpiration: false
      maxDeliveryCount: 5
    }
  }

  resource queueToService 'queues@2017-04-01' = {
    name: 'tempcontroller-receiver'
    properties: {
      defaultMessageTimeToLive: 'PT5M'
      deadLetteringOnMessageExpiration: false
      maxDeliveryCount: 5
    }
  }
}
