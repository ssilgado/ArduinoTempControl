param(
    [parameter( HelpMessage = "The name of the deployment.")]
    [string]$Name,

    [parameter( HelpMessage = "The name of the resource group to deploy to.")]
    [string]$ResourceGroupName,

    [parameter( HelpMessage = "The path of the bicep file.")]
    [string]$TemplateFilePath,

    [parameter( HelpMessage = "The path of the parameters file.")]
    [string]$ParametersFilePath
)

Write-Host "Deploying to Resource Group $ResourceGroupName"
Write-Host "Deployment Name: $Name"
Write-Host "Template File: $TemplateFilePath"
Write-Host "Parameters File: $ParametersFilePath"

# Deploy the template
az deployment group create `
    --name $Name `
    --resource-group $ResourceGroupName `
    --template-file $TemplateFilePath `
    --parameters @$ParametersFilePath

Write-Host "Deployment complete"
