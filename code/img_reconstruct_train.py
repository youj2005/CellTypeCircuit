import torch.nn as nn
from torch.utils.data import DataLoader
import torch.optim as optim
import torch
import pickle
import numpy as np
import matplotlib.pyplot as plt

# Variables

scratch_dir = "/storage/ice1/7/8/jyou79/base_a0.07_pf0.0"
cifar_dir = "/storage/ice1/7/8/jyou79/cifar-10-batches-py"
storage_dir = "/storage/ice1/7/8/jyou79"
images = 900

# Define the PyTorch model
class ReconstructImageModel(nn.Module):
    def __init__(self, input_size=32*32, output_size=32*32):
        super(ReconstructImageModel, self).__init__()
        self.fc1 = nn.Linear(input_size, output_size)
        self.sigmoid = nn.Sigmoid()  # For image pixel values between 0 and 1

    def forward(self, x):
        x = self.fc1(x)
        return x
    
import pickle
import numpy as np

print("Start")

def rgb_to_grayscale(row):
        R = row[:1024].reshape(32, 32)
        G = row[1024:2048].reshape(32, 32)
        B = row[2048:].reshape(32, 32)
        grayscale = 0.299 * R + 0.587 * G + 0.114 * B
        return grayscale
   
with open(f'%s/data_batch_1'%(cifar_dir), 'rb') as f:
        cifar = pickle.load(f, encoding='bytes') 
cifar = np.array([rgb_to_grayscale(row) for row in cifar[b'data']])
cifar = cifar.astype(np.uint8)

def binning(rates, positions, dimension):
    H, xedges, yedges = np.histogram2d(
        x=positions[:, 0],
        y=positions[:, 1],
        bins=dimension,
        range=[[0, 1], [0, 1]],
        weights=rates
    )
    
    # 2. Count of the neurons in each bin (this time no weights).
    C, _, _ = np.histogram2d(
        x=positions[:, 0],
        y=positions[:, 1],
        bins=dimension,
        range=[[0, 1], [0, 1]]
    )

    with np.errstate(divide='ignore', invalid='ignore'):
        reconstructed = H / C
        reconstructed[np.isnan(reconstructed)] = 0
    
    return reconstructed

train_dataset = []

for i in range(images):
    with open(f'%s/results_{i}/1_positions.pickle'%(scratch_dir), 'rb') as f:
        positions = pickle.load(f, encoding='bytes') 
        
    with open(f'%s/results_{i}/1_rates.pickle'%(scratch_dir), 'rb') as f:
        rates = pickle.load(f, encoding='bytes') 

    exc_rates = np.array(rates[:8000])
    pv_rates = np.array(rates[8000:9000])
    sst_rates = np.array(rates[9000:])

    exc_positions = np.array(positions[:8000])
    pv_positions = np.array(positions[8000:9000])
    sst_positions = np.array(positions[9000:])

    exc_binned = binning(exc_rates, exc_positions, 64)
    pv_binned = binning(pv_rates, pv_positions, 64)
    sst_binned = binning(sst_rates, sst_positions, 64)
    
    binned = np.concatenate((exc_binned, pv_binned, sst_binned)).reshape(-1)
    
    train_dataset.append(binned)
    
train_dataset = np.array(train_dataset) 
model = ReconstructImageModel(input_size=64*64*3, output_size=32*32)
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001, weight_decay=0.001)
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
train_dataset = torch.tensor(train_dataset, dtype=torch.float, device=device)
target_dataset = torch.tensor(cifar[:images].reshape(-1, 32*32), dtype=torch.float, device=device)
model.to(device)

lossl = []

num_epochs = 10
model.train()
for epoch in range(num_epochs):
    for i in range(len(train_dataset)):
        optimizer.zero_grad()
        outputs = model(train_dataset[i])
        loss = criterion(outputs, target_dataset[i])
        loss.backward()
        optimizer.step()
        lossl.append(loss.item())
        
torch.save(model, f'%s/model.pth'%(scratch_dir))
with open(f'%s/loss.pickle'%(scratch_dir), 'wb') as f:
    pickle.dump(lossl, f)
    
print("End")