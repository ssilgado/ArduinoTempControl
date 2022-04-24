param(
    [parameter()]
    [Description("The name of the deployment.")]
    [string]$Name,

    [parameter()]
    [Description("The name of the resource group to deploy to.")]
    [string]$ResourceGroupName,

    [parameter()]
    [Description("The path of the bicep file.")]
    [string]$TemplateFilePath,

    [parameter()]
    [Description("The path of the parameters file.")]
    [string]$ParametersFilePath,
)

Write-Host "Deploying to Resource Group $ResourceGroupName"
Write-Host "Deployment Name: $Name"
Write-Host "Template File: $TemplateFilePath"
Write-Host "Parameters File: $ParametersFilePath"

# Parse parameters file to json object
$Parameters = ConvertFrom-Json -InputObject (Get-Content $ParametersFilePath)

# Deploy the template
az group deployment create \
    --name $Name \
    --resource-group $ResourceGroupName \
    --template-file $TemplateFilePath \
    --parameters $Parameters

Write-Host "Deployment complete"
